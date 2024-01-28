#include "CustomShaderRunner.h"

#if !UE_BUILD_SHIPPING
#include "Editor.h"
#endif

#include "Engine/World.h"
#include "SceneInterface.h"
#include "Renderer/Private/ScenePrivate.h"

static int GUseRaycastCustom = 1;
FAutoConsoleVariableRef CUseRaycastCustom(
TEXT("Keti.Sensor.UseRaycastCustom"),
GUseRaycastCustom,
TEXT("default 1\n"),
ECVF_Cheat
);
 
ACustomShaderRunner::ACustomShaderRunner()
{
    USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    RootComponent = SceneComponent;

    PrimaryActorTick.bCanEverTick = true;
}
 
// Called when the game starts or when spawned
void ACustomShaderRunner::BeginPlay()
{
    Super::BeginPlay();
    TestCustomRaycast = FCustomRaycastHwrt();
    Initialized = false;
 
    if (RTRaycast != nullptr)
        UpdateTestParameters();

#if !UE_BUILD_SHIPPING
    if (GetWorld()->IsPlayInEditor())
    {
        FEditorDelegates::OnPreSwitchBeginPIEAndSIE.AddStatic(&ACustomShaderRunner::StaticToggleEditorSimulateMode);
    }
#endif
}
 
void ACustomShaderRunner::UpdateTestParameters()
{
    FCustomRaycastRHIParameters parameters;
    parameters.Scene = &GetWorld()->Scene->GetRenderScene()->RayTracingScene;
    parameters.CachedRenderTargetSize = FIntPoint(RTRaycast->SizeX, RTRaycast->SizeY);
    parameters.RenderTarget = RTRaycast;
    TestCustomRaycast.UpdateParameters(parameters);
}
 
// Called every frame
void ACustomShaderRunner::Tick(float DeltaTime)
{
    if (GUseRaycastCustom != 1)
    {
        EndRendering();
        return;
    }
    
    FRayTracingScene* rtScene = &GetWorld()->Scene->GetRenderScene()->RayTracingScene;
    bool isInitializedRT = rtScene->IsCreated();
    if (isInitializedRT == false)
    {
        return;
    }
    
    TranscurredTime+=DeltaTime;
    Super::Tick(DeltaTime);
 
    // we want a slight delay before we start, otherwise some resources such as the accelerated structure will not be ready
    if(RTRaycast != nullptr && TranscurredTime>1.0f)
    {
        UpdateTestParameters();
 
        if(!Initialized)
        {
            TestCustomRaycast.BeginRendering();
            Initialized = true;
        }
    }
}
void ACustomShaderRunner::BeginDestroy()
{
    Super::BeginDestroy();
    EndRendering();
}

void ACustomShaderRunner::EndRendering()
{
    TestCustomRaycast.EndRendering();
    Initialized = false;
}

void ACustomShaderRunner::StaticToggleEditorSimulateMode(bool bSimulateOnEditor)
{
    GUseRaycastCustom = bSimulateOnEditor;
}
