// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HideAndSeekWithAITarget : TargetRules
{
	public HideAndSeekWithAITarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("HideAndSeekWithAI");
	}
}