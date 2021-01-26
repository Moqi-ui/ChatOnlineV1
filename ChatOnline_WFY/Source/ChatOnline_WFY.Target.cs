// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ChatOnline_WFYTarget : TargetRules
{
	public ChatOnline_WFYTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		//DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ChatOnline_WFY");
	}
}
