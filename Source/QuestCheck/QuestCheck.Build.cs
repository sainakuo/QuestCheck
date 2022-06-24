// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuestCheck : ModuleRules
{
	public QuestCheck(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "QuestSystem"});
	}
}
