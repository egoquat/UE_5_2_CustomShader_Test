#include "CustomRaycastHwrt.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderTargetPool.h"
#include "RHI.h"
#include "Modules/ModuleManager.h"
#include "RayTracingDefinitions.h"
#include "RayTracingPayloadType.h"
#include "../Private/RayTracing/RayTracingScene.h"
#include "../Private/SceneRendering.h"
#include "RenderGraphUtils.h"
 
#define NUM_THREADS_PER_GROUP_DIMENSION 8

struct FVFXTracePayload
{
    float HitT;
    uint32 PrimitiveIndex;
    uint32 InstanceIndex;
    float Barycentrics[2];
    float WorldPosition[3];
    float WorldNormal[3];
};

class FCustomRaycastRHIRGS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FCustomRaycastRHIRGS)
	SHADER_USE_ROOT_PARAMETER_STRUCT(FCustomRaycastRHIRGS, FGlobalShader)
	
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
    
		SHADER_PARAMETER_UAV(RWTexture2D<float4>, outTex)
		SHADER_PARAMETER_SRV(RaytracingAccelerationStructure, TLAS)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, ViewUniformBuffer)
	END_SHADER_PARAMETER_STRUCT()
 
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}
 
	static ERayTracingPayloadType GetRayTracingPayloadType(const int32 /*PermutationId*/)
	{
		return ERayTracingPayloadType::VFX;
	}
 
	static inline void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
 
		//We're using it here to add some preprocessor defines. That way we don't have to change both C++ and HLSL code when we change the value for NUM_THREADS_PER_GROUP_DIMENSION
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_X"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Y"), NUM_THREADS_PER_GROUP_DIMENSION);
		OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Z"), NUM_THREADS_PER_GROUP_DIMENSION);

	    OutEnvironment.SetDefine(TEXT("VF_SUPPORTS_PRIMITIVE_SCENE_DATA"), 1);
	    OutEnvironment.SetDefine(TEXT("USE_GLOBAL_GPU_SCENE_DATA"), 1);
	    OutEnvironment.SetDefine(TEXT("RT_PAYLOAD_TYPE"), static_cast<int32>(ERayTracingPayloadType::VFX));
	}
};
 
class FCustomRaycastRHICHS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FCustomRaycastRHICHS)
	//SHADER_USE_ROOT_PARAMETER_STRUCT(FCustomRaycastRHICHS, FGlobalShader)
 
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}
 
	static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)
	{
	    return ERayTracingPayloadType::VFX;
	}
    
	using FParameters = FEmptyShaderParameters;

    FCustomRaycastRHICHS() = default;
    FCustomRaycastRHICHS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {}
};
 
class FCustomRaycastRHIMS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FCustomRaycastRHIMS)
	//SHADER_USE_ROOT_PARAMETER_STRUCT(FCustomRaycastRHIMS, FGlobalShader)
 
    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}
 
	static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)
	{
	    return ERayTracingPayloadType::VFX;
	}
 
	using FParameters = FEmptyShaderParameters;

    FCustomRaycastRHIMS() = default;
    FCustomRaycastRHIMS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {}
};

IMPLEMENT_GLOBAL_SHADER(FCustomRaycastRHIRGS, "/CustomShaders/CustomRaycastTestShader.usf", "RayTraceTestRGS", SF_RayGen);
IMPLEMENT_GLOBAL_SHADER(FCustomRaycastRHICHS, "/CustomShaders/CustomRaycastTestShader.usf", "RayTraceTestCHS", SF_RayHitGroup);
IMPLEMENT_GLOBAL_SHADER(FCustomRaycastRHIMS,  "/CustomShaders/CustomRaycastTestShader.usf", "RayTraceTestMS", SF_RayMiss);
 
FCustomRaycastHwrt::FCustomRaycastHwrt()
{
}
 
void FCustomRaycastHwrt::BeginRendering()
{
	//If the handle is already initialized and valid, no need to do anything
	if (PostOpaqueRenderDelegate.IsValid())
	{
		return;
	}
	//Get the Renderer Module and add our entry to the callbacks so it can be executed each frame after the scene rendering is done
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		PostOpaqueRenderDelegate = RendererModule->RegisterPostOpaqueRenderDelegate(FPostOpaqueRenderDelegate::CreateRaw(this, &FCustomRaycastHwrt::Execute_RenderThread));
	}
 
	// create output texture
	FIntPoint TextureSize = { CachedParams.RenderTarget->SizeX, CachedParams.RenderTarget->SizeY };
	FRHITextureCreateDesc TextureDesc = FRHITextureCreateDesc::Create2D(TEXT("RaytracingTestOutput"), TextureSize.X, TextureSize.Y, CachedParams.RenderTarget->GetFormat());
	TextureDesc.AddFlags(TexCreate_ShaderResource | TexCreate_UAV);
	ShaderOutputTexture = RHICreateTexture(TextureDesc);
	ShaderOutputTextureUAV = RHICreateUnorderedAccessView(ShaderOutputTexture);
}
 
//Stop the compute shader execution
void FCustomRaycastHwrt::EndRendering()
{
	//If the handle is not valid then there's no cleanup to do
	if (!PostOpaqueRenderDelegate.IsValid())
	{
		return;
	}
	//Get the Renderer Module and remove our entry from the PostOpaqueRender callback
	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		RendererModule->RemovePostOpaqueRenderDelegate(PostOpaqueRenderDelegate);
	}
 
	PostOpaqueRenderDelegate.Reset();
}
 
void FCustomRaycastHwrt::UpdateParameters(FCustomRaycastRHIParameters& DrawParameters)
{
	CachedParams = DrawParameters;
	bCachedParamsAreValid = true;
}
 
void FCustomRaycastHwrt::Execute_RenderThread(FPostOpaqueRenderParameters& Parameters)
#if RHI_RAYTRACING
{
	FRDGBuilder* GraphBuilder = Parameters.GraphBuilder;
	FRHICommandListImmediate& RHICmdList = GraphBuilder->RHICmdList;
	//If there's no cached parameters to use, skip
	//If no Render Target is supplied in the cachedParams, skip
	if (!(bCachedParamsAreValid && CachedParams.RenderTarget))
	{
		return;
	}

    bool isOutTextureReady = ShaderOutputTexture.IsValid() == true;
    if (isOutTextureReady == false) return;
    
	//Render Thread Assertion
	check(IsInRenderingThread());
 
	// set shader parameters
	FCustomRaycastRHIRGS::FParameters *PassParameters = GraphBuilder->AllocParameters<FCustomRaycastRHIRGS::FParameters>();
	PassParameters->ViewUniformBuffer = Parameters.View->ViewUniformBuffer;
	PassParameters->TLAS = CachedParams.Scene->GetLayerSRVChecked(ERayTracingSceneLayer::Base);
	PassParameters->outTex = ShaderOutputTextureUAV;
 
	// define render pass needed parameters
	TShaderMapRef<FCustomRaycastRHIRGS> CustomRaycastRHIRGS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	FIntPoint TextureSize = { CachedParams.RenderTarget->SizeX, CachedParams.RenderTarget->SizeY };
	FRHIRayTracingScene* RHIScene = CachedParams.Scene->GetRHIRayTracingScene();
    //FRHIRayTracingScene* RHIScene = Parameters.View->GetRayTracingSceneChecked();
 
	// add the ray trace dispatch pass
	GraphBuilder->AddPass(
		RDG_EVENT_NAME("CustomRaycastHwrt"),
		PassParameters,
		ERDGPassFlags::Compute,
		[PassParameters, CustomRaycastRHIRGS, TextureSize, RHIScene](FRHIRayTracingCommandList& RHICmdList)
		{
			FRayTracingShaderBindingsWriter GlobalResources;
			SetShaderParameters(GlobalResources, CustomRaycastRHIRGS, *PassParameters);
 
			FRayTracingPipelineStateInitializer PSOInitializer;
			PSOInitializer.MaxPayloadSizeInBytes = sizeof(FVFXTracePayload);
			PSOInitializer.bAllowHitGroupIndexing = false;
 
			// Set RayGen shader
			TArray<FRHIRayTracingShader*> RayGenShaderTable;
			RayGenShaderTable.Add(GetGlobalShaderMap(GMaxRHIFeatureLevel)->GetShader<FCustomRaycastRHIRGS>().GetRayTracingShader());
			PSOInitializer.SetRayGenShaderTable(RayGenShaderTable);
 
			// Set ClosestHit shader
			TArray<FRHIRayTracingShader*> RayHitShaderTable;
			RayHitShaderTable.Add(GetGlobalShaderMap(GMaxRHIFeatureLevel)->GetShader<FCustomRaycastRHICHS>().GetRayTracingShader());
			PSOInitializer.SetHitGroupTable(RayHitShaderTable);
			
			// Set Miss shader
			TArray<FRHIRayTracingShader*> RayMissShaderTable;
			RayMissShaderTable.Add(GetGlobalShaderMap(GMaxRHIFeatureLevel)->GetShader<FCustomRaycastRHIMS>().GetRayTracingShader());
			PSOInitializer.SetMissShaderTable(RayMissShaderTable);
 
			// dispatch ray trace shader
			FRayTracingPipelineState* PipeLine = PipelineStateCache::GetAndOrCreateRayTracingPipelineState(RHICmdList, PSOInitializer);
			RHICmdList.SetRayTracingMissShader(RHIScene, 0, PipeLine, 0 /* ShaderIndexInPipeline */, 0, nullptr, 0);
			RHICmdList.RayTraceDispatch(PipeLine, CustomRaycastRHIRGS.GetRayTracingShader(), RHIScene, GlobalResources, TextureSize.X, TextureSize.Y);
		}
	);
 
	// Copy textures from the shader output to our render target
	// this is done as a render pass with the graph builder
	FTexture2DRHIRef OriginalRT = CachedParams.RenderTarget->GetRenderTargetResource()->GetTexture2DRHI();
	FRDGTexture* OutputRDGTexture = GraphBuilder->RegisterExternalTexture(CreateRenderTarget(ShaderOutputTexture, TEXT("RaytracingTestOutputRT")));
	FRDGTexture* CopyToRDGTexture = GraphBuilder->RegisterExternalTexture(CreateRenderTarget(OriginalRT, TEXT("RaytracingTestCopyToRT")));
	FRHICopyTextureInfo CopyInfo;
	CopyInfo.Size = FIntVector(TextureSize.X, TextureSize.Y, 0);
	AddCopyTexturePass(*GraphBuilder, OutputRDGTexture, CopyToRDGTexture, CopyInfo);
}
#else // !RHI_RAYTRACING
{
	unimplemented();
}
#endif