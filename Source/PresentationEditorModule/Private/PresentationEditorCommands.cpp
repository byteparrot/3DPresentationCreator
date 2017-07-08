#include "PresentationEditorModulePCH.h"

#if WITH_EDITOR

#include "PresentationEditorCommands.h"
#include "PluginManager.h"
#include "ObjectTools.h"
#include "UnrealEd.h"

#define LOCTEXT_NAMESPACE "PresentationEditorCommands"

void PresentationEditorCommands::RegisterCommands()
{
	UI_COMMAND(ToolsButton, "Tools", "Tools", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(NewSlide, "NewSlide", "NewSlide", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(NewCustomDesign, "NewCustomDesign", "NewCustomDesign", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ConfigureButton, "Configure", "Configure", EUserInterfaceActionType::Button, FInputGesture());
}

void PresentationEditorCommands::OpenPresentationTools_Clicked()
{
	TSharedRef<class FGlobalTabmanager> tm = FGlobalTabmanager::Get();
	tm->InvokeTab(PresentationTabName);	
}

void PresentationEditorCommands::NewSlide_Clicked()
{
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world
	if (World) {
		ConfigurePresentation_Clicked();	
		PluginManager::getInstance()->spawnSlide(World);
		UE_LOG(PresentationPluginLog, Log, TEXT("Placed New Slide!"));
	}
}

void PresentationEditorCommands::NewCustomDesign_Clicked()
{
	FStringAssetReference MyAssetPath(TEXT("/PresentationPlugin/Slide_Custom"));
	UObject* MyAsset = MyAssetPath.TryLoad();

	CopyAsset(MyAsset, FString("/Game"));
}

void PresentationEditorCommands::ConfigurePresentation_Clicked()
{
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world
	if (World) {

		AWorldSettings* worldSettings = World->GetWorldSettings();

		if(worldSettings->DefaultGameMode != PluginManager::getInstance()->getGameModeClass())
			PluginManager::printMessageBox(LOCTEXT("ConfigurePresentation", "Project is now in Presentation Mode!"));

		worldSettings->DefaultGameMode = PluginManager::getInstance()->getGameModeClass();

		World->ReloadConfig();
	}
}

void PresentationEditorCommands::CopyAsset(UObject* Asset, const FString& DestPath)
{
	TArray<UObject*> Assets = { Asset };
	ObjectTools::DuplicateObjects(Assets, TEXT(""), DestPath, /*bOpenDialog=*/true);
}

#endif

#undef LOCTEXT_NAMESPACE
