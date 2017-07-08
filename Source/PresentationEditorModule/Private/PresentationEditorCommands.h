#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Commands.h"
#include "EditorStyle.h"

/**
* PresentationEditorCommands represents the commands that are used within this plugin on buttons
*/
class PresentationEditorCommands : public TCommands<PresentationEditorCommands>
{
public:

	PresentationEditorCommands(): TCommands<PresentationEditorCommands>(TEXT("PresentationEditorCommands"), NSLOCTEXT("Contexts", "PresentationPlugin", "PresentationPlugin"), NAME_None, FEditorStyle::GetStyleSetName()){}

	/**
	* Initialize commands
	*/
	virtual void RegisterCommands() override;

	TSharedPtr< FUICommandInfo > ToolsButton;
	TSharedPtr< FUICommandInfo > NewSlide;
	TSharedPtr< FUICommandInfo > NewCustomDesign;
	TSharedPtr< FUICommandInfo > ConfigureButton;

	static void NewSlide_Clicked();
	static void OpenPresentationTools_Clicked();
	static void ConfigurePresentation_Clicked();
	static void NewCustomDesign_Clicked();

	/**
	* CopyAsset is used to create a new custom umg slide template by copying a sample slide from the plugin to a user chosen destination
	*/
	static void CopyAsset(UObject* Asset, const FString& DestPath);

};

#endif