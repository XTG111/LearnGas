// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GasRPGDemo1 : ModuleRules
{
	public GasRPGDemo1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayAbilities" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks", "AnimGraphRuntime", "AnimGraphRuntime" });

    }
}
