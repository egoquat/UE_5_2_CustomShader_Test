// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_CustomShader_TestGameMode.h"
#include "UE_CustomShader_TestPawn.h"
#include "UE_CustomShader_TestHud.h"

AUE_CustomShader_TestGameMode::AUE_CustomShader_TestGameMode()
{
	DefaultPawnClass = AUE_CustomShader_TestPawn::StaticClass();
	HUDClass = AUE_CustomShader_TestHud::StaticClass();
}
