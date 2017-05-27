// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DCEditorTarget : TargetRules
{
	public DCEditorTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Editor;
        ExtraModuleNames.Add("DC");
    }

	//
	// TargetRules interface.
	//

	//public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.Add("DC");
	//}
}
