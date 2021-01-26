// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ChatOnline_WFYEditorTarget : TargetRules
{
	public ChatOnline_WFYEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		//DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ChatOnline_WFY");
	}
}
