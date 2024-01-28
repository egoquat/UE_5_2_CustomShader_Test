// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue5_vehicle_testWheelRear.h"
#include "UObject/ConstructorHelpers.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

Uue5_vehicle_testWheelRear::Uue5_vehicle_testWheelRear()
{
	WheelRadius = 40.f;
	WheelWidth = 40.0f;
	FrictionForceMultiplier = 4.0f;
	CorneringStiffness = 1200.0f;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = false;
	AxleType = EAxleType::Rear;
	SpringRate = 250.0f;
	SpringPreload = 50.f;
	SuspensionDampingRatio = 0.5f;
	WheelLoadRatio = 0.5f;
	RollbarScaling = 0.5f;
	SuspensionMaxRaise = 10.0f;
	SuspensionMaxDrop = 10.0f;
	WheelLoadRatio = 0.5f;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS
