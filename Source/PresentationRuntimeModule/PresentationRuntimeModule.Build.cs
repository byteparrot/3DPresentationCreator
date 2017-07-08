// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class PresentationRuntimeModule : ModuleRules
    {
        public PresentationRuntimeModule(ReadOnlyTargetRules Target) : base(Target)
        {
            PublicIncludePaths.AddRange(
                new string[] {
                    "PresentationRuntimeModule/Public"
                    // ... add public include paths required here ...
                }
            );

            PrivateIncludePaths.AddRange(
                new string[] {
                    "PresentationRuntimeModule/Private"
                    // ... add other private include paths required here ...
                }
            );

            if (UEBuildConfiguration.bBuildEditor)
            {
                PublicDependencyModuleNames.AddRange(
                    new string[]
                    {
                        //"InputCore"//,
                        "UnrealEd"//,
                        //"Slate",
                        //"SlateCore",
                        //"EditorStyle",
                        //"UMG",
                        //"ClassViewer"
                        // ... add other public dependencies that you statically link with here ...
                    }
                );
            }

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine"//,
                    //"InputCore"//,
                    //"UnrealEd",
                    //"Slate",
                    //"SlateCore",
                    //"EditorStyle",
                    //"UMG",
                    //"ClassViewer"
                    // ... add other public dependencies that you statically link with here ...
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    // ... add private dependencies that you statically link with here ...
                }
            );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
            );
        }
    }
}