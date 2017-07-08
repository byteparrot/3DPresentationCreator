// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class PresentationEditorModule : ModuleRules
	{
		public PresentationEditorModule(ReadOnlyTargetRules Target) : base(Target)
		{
		    PublicIncludePaths.AddRange(
		        new string[] {
		            "PresentationEditorModule/Public"
		            // ... add public include paths required here ...
		        }
		    );

		    PrivateIncludePaths.AddRange(
		        new string[] {
		            "PresentationEditorModule/Private"
		            // ... add other private include paths required here ...
		        }
		    );

		    PublicDependencyModuleNames.AddRange(
		        new string[]
		        {
		            "Core",
		            "CoreUObject",
		            "Engine",
		            "InputCore",
		            "UnrealEd",
		            "Slate",
		            "SlateCore",
		            "EditorStyle",
                    "UMG",
                    "ClassViewer"
		            // ... add other public dependencies that you statically link with here ...
		        }
		    );

		    PrivateDependencyModuleNames.AddRange(
		        new string[]
		        {
                    "PresentationRuntimeModule"
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