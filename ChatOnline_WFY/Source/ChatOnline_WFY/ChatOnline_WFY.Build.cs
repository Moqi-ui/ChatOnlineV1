// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChatOnline_WFY : ModuleRules
{
	public ChatOnline_WFY(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","GMESDK", "UMG" , "SimpleThread", "SimpleNetChannel" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "Json", "JsonUtilities" });
	}
}
