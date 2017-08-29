// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PresentationEditorModuleCommands.h"
#include "PluginManager.h"
#include "ObjectTools.h"
#include "UnrealEd.h"

#define LOCTEXT_NAMESPACE "FPresentationEditorModuleModule"

void FPresentationEditorModuleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "PresentationTools", "Bring up PresentationPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

void FPresentationEditorModuleCommands::NewSlide_Clicked()
{
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world
	if (World) {
		ConfigurePresentation_Clicked();
		PluginManager::getInstance()->spawnSlide(World);
		UE_LOG(LogTemp, Log, TEXT("Placed New Slide!"));
	}
}

void FPresentationEditorModuleCommands::NewCustomDesign_Clicked()
{
	FStringAssetReference MyAssetPath(TEXT("/PresentationPlugin/Slide_Custom"));
	UObject* MyAsset = MyAssetPath.TryLoad();

	CopyAsset(MyAsset, FString("/Game"));
}

void FPresentationEditorModuleCommands::ConfigurePresentation_Clicked()
{
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world
	if (World) {

		AWorldSettings* worldSettings = World->GetWorldSettings();

		if (worldSettings->DefaultGameMode != PluginManager::getInstance()->getGameModeClass())
			PluginManager::printMessageBox(LOCTEXT("ConfigurePresentation", "Project is now in Presentation Mode!"));

		worldSettings->DefaultGameMode = PluginManager::getInstance()->getGameModeClass();

		World->ReloadConfig();
	}
}

void FPresentationEditorModuleCommands::CopyAsset(UObject* Asset, const FString& DestPath)
{
	TArray<UObject*> Assets = { Asset };
	ObjectTools::DuplicateObjects(Assets, TEXT(""), DestPath, /*bOpenDialog=*/true);
}

#undef LOCTEXT_NAMESPACE
