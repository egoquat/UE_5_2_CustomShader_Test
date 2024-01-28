// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ue5_vehicle_testHud.generated.h"

UCLASS(config = Game)
class Aue5_vehicle_testHud : public AHUD
{
	GENERATED_BODY()

public:
	Aue5_vehicle_testHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
