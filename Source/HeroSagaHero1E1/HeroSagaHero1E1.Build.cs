// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HeroSagaHero1E1 : ModuleRules
{
	public HeroSagaHero1E1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
