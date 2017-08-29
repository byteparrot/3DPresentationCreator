// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PresentationEditorModuleStyle.h"

class FPresentationEditorModuleCommands : public TCommands<FPresentationEditorModuleCommands>
{
public:

	FPresentationEditorModuleCommands()
		: TCommands<FPresentationEditorModuleCommands>(TEXT("PresentationPlugin"), NSLOCTEXT("Contexts", "PresentationsPlugin", "PresentationsPlugin Plugin"), NAME_None, FPresentationEditorModuleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
	
	static void NewSlide_Clicked();
	static void ConfigurePresentation_Clicked();
	static void NewCustomDesign_Clicked();
	/**
	* CopyAsset is used to create a new custom umg slide template by copying a sample slide from the plugin to a user chosen destination
	*/
	static void CopyAsset(UObject* Asset, const FString& DestPath);
};