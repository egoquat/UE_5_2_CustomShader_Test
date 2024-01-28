// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ue5_vehicle_test : ModuleRules
{
	public ue5_vehicle_test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ChaosVehicles", "HeadMountedDisplay", "PhysicsCore",
					"CustomShader" });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
