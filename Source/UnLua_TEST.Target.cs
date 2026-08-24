// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnLua_TESTTarget : TargetRules
{
	public UnLua_TESTTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("UnLua_TEST");
		GlobalDefinitions.Add("__has_feature(x)=0");
		bOverrideBuildEnvironment = true;
		bUndefinedIdentifierErrors = false;
	}
}
