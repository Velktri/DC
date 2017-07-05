// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DC : ModuleRules
{
	public DC(ReadOnlyTargetRules Target) : base (Target)
	{
        PrivateIncludePaths.AddRange(
            new string[] {
                "DC/Private/UI/Widgets",
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "HeadMountedDisplay",
                "UMG",
                "Slate",
                "SlateCore"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "UMG",
                "Slate",
                "SlateCore"
            }
        );
    }
}
