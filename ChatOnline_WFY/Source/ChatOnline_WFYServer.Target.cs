// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ChatOnline_WFYServerTarget : TargetRules
{
	public ChatOnline_WFYServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		//DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ChatOnline_WFY");
	}
}
