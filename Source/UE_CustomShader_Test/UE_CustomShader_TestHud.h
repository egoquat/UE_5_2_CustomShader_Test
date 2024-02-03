// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UE_CustomShader_TestHud.generated.h"

UCLASS(config = Game)
class AUE_CustomShader_TestHud : public AHUD
{
	GENERATED_BODY()

public:
	AUE_CustomShader_TestHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
