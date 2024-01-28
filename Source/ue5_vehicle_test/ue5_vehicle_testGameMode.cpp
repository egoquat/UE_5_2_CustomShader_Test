// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue5_vehicle_testGameMode.h"
#include "ue5_vehicle_testPawn.h"
#include "ue5_vehicle_testHud.h"

Aue5_vehicle_testGameMode::Aue5_vehicle_testGameMode()
{
	DefaultPawnClass = Aue5_vehicle_testPawn::StaticClass();
	HUDClass = Aue5_vehicle_testHud::StaticClass();
}
