// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CustomShader/Public/CustomShaderRunner.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomShaderRunner() {}
// Cross Module References
	CUSTOMSHADER_API UClass* Z_Construct_UClass_ACustomShaderRunner();
	CUSTOMSHADER_API UClass* Z_Construct_UClass_ACustomShaderRunner_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	UPackage* Z_Construct_UPackage__Script_CustomShader();
// End Cross Module References
	void ACustomShaderRunner::StaticRegisterNativesACustomShaderRunner()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACustomShaderRunner);
	UClass* Z_Construct_UClass_ACustomShaderRunner_NoRegister()
	{
		return ACustomShaderRunner::StaticClass();
	}
	struct Z_Construct_UClass_ACustomShaderRunner_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RTRaycast_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RTRaycast;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACustomShaderRunner_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_CustomShader,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACustomShaderRunner_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CustomShaderRunner.h" },
		{ "ModuleRelativePath", "Public/CustomShaderRunner.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACustomShaderRunner_Statics::NewProp_RTRaycast_MetaData[] = {
		{ "Category", "ShaderDemo" },
		{ "ModuleRelativePath", "Public/CustomShaderRunner.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACustomShaderRunner_Statics::NewProp_RTRaycast = { "RTRaycast", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ACustomShaderRunner, RTRaycast), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ACustomShaderRunner_Statics::NewProp_RTRaycast_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACustomShaderRunner_Statics::NewProp_RTRaycast_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACustomShaderRunner_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACustomShaderRunner_Statics::NewProp_RTRaycast,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACustomShaderRunner_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACustomShaderRunner>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACustomShaderRunner_Statics::ClassParams = {
		&ACustomShaderRunner::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ACustomShaderRunner_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ACustomShaderRunner_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ACustomShaderRunner_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACustomShaderRunner_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACustomShaderRunner()
	{
		if (!Z_Registration_Info_UClass_ACustomShaderRunner.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACustomShaderRunner.OuterSingleton, Z_Construct_UClass_ACustomShaderRunner_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACustomShaderRunner.OuterSingleton;
	}
	template<> CUSTOMSHADER_API UClass* StaticClass<ACustomShaderRunner>()
	{
		return ACustomShaderRunner::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACustomShaderRunner);
	ACustomShaderRunner::~ACustomShaderRunner() {}
	struct Z_CompiledInDeferFile_FID_Test_ue5_vehicle_test_Plugins_CustomShader_Source_CustomShader_Public_CustomShaderRunner_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test_ue5_vehicle_test_Plugins_CustomShader_Source_CustomShader_Public_CustomShaderRunner_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACustomShaderRunner, ACustomShaderRunner::StaticClass, TEXT("ACustomShaderRunner"), &Z_Registration_Info_UClass_ACustomShaderRunner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACustomShaderRunner), 476391858U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test_ue5_vehicle_test_Plugins_CustomShader_Source_CustomShader_Public_CustomShaderRunner_h_2518513656(TEXT("/Script/CustomShader"),
		Z_CompiledInDeferFile_FID_Test_ue5_vehicle_test_Plugins_CustomShader_Source_CustomShader_Public_CustomShaderRunner_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test_ue5_vehicle_test_Plugins_CustomShader_Source_CustomShader_Public_CustomShaderRunner_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
