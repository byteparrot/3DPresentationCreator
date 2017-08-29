// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PresentationEditorModule.h"
#include "PresentationEditorModuleStyle.h"
#include "PresentationEditorModuleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "PresentationToolsWidget.h"

static const FName PresentationsPluginTabName("PresentationsPlugin");

#define LOCTEXT_NAMESPACE "FPresentationEditorModuleModule"

void FPresentationEditorModuleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPresentationEditorModuleStyle::Initialize();
	FPresentationEditorModuleStyle::ReloadTextures();

	FPresentationEditorModuleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPresentationEditorModuleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPresentationEditorModuleModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPresentationEditorModuleModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPresentationEditorModuleModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PresentationsPluginTabName, FOnSpawnTab::CreateRaw(this, &FPresentationEditorModuleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPresentationsPluginTabTitle", "PresentationsPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPresentationEditorModuleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FPresentationEditorModuleStyle::Shutdown();

	FPresentationEditorModuleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PresentationsPluginTabName);
}

TSharedRef<SDockTab> FPresentationEditorModuleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPresentationEditorModuleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PresentationEditorModule.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(PresentationToolsWidget)
		];
}

void FPresentationEditorModuleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(PresentationsPluginTabName);
}

void FPresentationEditorModuleModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FPresentationEditorModuleCommands::Get().OpenPluginWindow);
}

void FPresentationEditorModuleModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FPresentationEditorModuleCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPresentationEditorModuleModule, PresentationPlugin)