#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomRaycastHwrt.h"
#include "CustomShaderRunner.generated.h"
 
UCLASS()
class CUSTOMSHADER_API ACustomShaderRunner : public AActor
{
    GENERATED_BODY()
	
public:	
    ACustomShaderRunner();
    FCustomRaycastHwrt TestCustomRaycast;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ShaderDemo)
    class UTextureRenderTarget2D* RTRaycast = nullptr;
	
protected:
    virtual void BeginPlay() override;
    void UpdateTestParameters();
 
    float TranscurredTime; ///< allows us to add a delay on BeginPlay() 
    bool Initialized;
 
public:	
    virtual void Tick(float DeltaTime) override;
    virtual void BeginDestroy() override;

    void EndRendering();

    static void StaticToggleEditorSimulateMode(bool bSimulateOnEditor); 
};
