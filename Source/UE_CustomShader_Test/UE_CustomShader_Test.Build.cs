// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_CustomShader_Test : ModuleRules
{
	public UE_CustomShader_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ChaosVehicles", "HeadMountedDisplay", "PhysicsCore",
					"CustomShader" });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
