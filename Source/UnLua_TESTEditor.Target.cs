// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnLua_TESTEditorTarget : TargetRules
{
	public UnLua_TESTEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("UnLua_TEST");
		
		
		bOverrideBuildEnvironment = true;
		bUndefinedIdentifierErrors = false;
	}
}
