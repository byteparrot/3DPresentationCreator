#include "PresentationEditorModulePCH.h"

#if WITH_EDITOR

#include "Modules/ModuleManager.h"
#include "PresentationEditorModule.h"
#include "LevelEditor.h"
#include "SDockTab.h"
#include "EditorStyle.h"

#include "PresentationToolsWidget.h"

#include "Engine.h"
#include "PresentationEditorCommands.h"


DEFINE_LOG_CATEGORY(PresentationPluginLog)

void PresentationEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	UE_LOG(PresentationPluginLog, Log, TEXT("Starting Extension logic"));

	if (IsAvailable()) {
		UE_LOG(PresentationPluginLog, Log, TEXT("Extension is loaded"));

		PresentationEditorCommands::Register();	// register the plugin commands in the engine
		BindCommands();	// bind the commands to the buttons

		toolbarExtender = MakeShareable(new FExtender); // create toolbar extender
		toolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, pluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &PresentationEditorModule::AddToolbarExtension)); // Add extender to the "Settings" hook

		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor"); // get reference to the unreal editor
		
		extensibilityManager = LevelEditorModule.GetToolBarExtensibilityManager();	// get the extensibility manager from the editor
		extensibilityManager->AddExtender(toolbarExtender);	// Add the toolbar extender to the manager so it can be created when the other buttons are created
		
		TSharedRef<class FGlobalTabmanager> tabmanager = FGlobalTabmanager::Get();	// get a reference to the global tab manager
		tabmanager->RegisterNomadTabSpawner(PresentationTabName, FOnSpawnTab::CreateRaw(this, &PresentationEditorModule::presentationTab))	// create and register the presentation tab in the tab manager
		  .SetDisplayName(FText::FromString(TEXT("PresentationTab")));
	}
	else {
		UE_LOG(PresentationPluginLog, Log, TEXT("Extension Load Error"));
	}
}


void PresentationEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (extensibilityManager.IsValid())
	{
		PresentationEditorCommands::Unregister();

		TSharedRef<class FGlobalTabmanager> tm = FGlobalTabmanager::Get();
		tm->UnregisterNomadTabSpawner(PresentationTabName);

		extensibilityManager->RemoveExtender(toolbarExtender);
		extensibilityManager.Reset();
	}
	else
	{
		extensibilityManager.Reset();
	}
}

void PresentationEditorModule::AddToolbarExtension(FToolBarBuilder& builder) const
{
#define LOCTEXT_NAMESPACE "PresentationEditorToolBar"

	// Add Toolbar button to quickly let the user create slides
	builder.AddToolBarButton(
		PresentationEditorCommands::Get().NewSlide, 
		NAME_None, 
		LOCTEXT("MyButton_Override", "New Slide"), 
		LOCTEXT("MyButton_ToolTipOverride", "Click to add a new slide to the camera position"), 
		FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.ViewOptions", "LevelEditor.ViewOptions.Small"),
		NAME_None
	);

	// Add Toolbar Combo Button for more presentation options
	builder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateStatic(&PresentationEditorModule::GeneratePresentationSettingsDropDownMenu, pluginCommands.ToSharedRef()),	// use pointer to the dropdownmenu creating function to be called on click
		LOCTEXT("QuickSettingsCombo", "PresentationTools"),
		LOCTEXT("QuickSettingsCombo_ToolTip", "Presentation Tools"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings"),
		false,
		NAME_None
	);

#undef LOCTEXT_NAMESPACE
}

TSharedRef<SDockTab> PresentationEditorModule::presentationTab(const FSpawnTabArgs& TabSpawnArgs) const
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).TabRole(ETabRole::NomadTab)[
		SNew(PresentationToolsWidget)
	];
	return SpawnedTab;
}

TSharedRef<SWidget> PresentationEditorModule::GeneratePresentationSettingsDropDownMenu(TSharedRef<FUICommandList> InCommandList)
{
#define LOCTEXT_NAMESPACE "PresentationEditorToolBarViewMenu"

	// Get all menu extenders for this context menu from the level editor module
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TArray<FLevelEditorModule::FLevelEditorMenuExtender> MenuExtenderDelegates = LevelEditorModule.GetAllLevelEditorToolbarViewMenuExtenders();
	TArray<TSharedPtr<FExtender>> Extenders;

	for (int32 i = 0; i < MenuExtenderDelegates.Num(); ++i)
	{
		if (MenuExtenderDelegates[i].IsBound())
		{
			Extenders.Add(MenuExtenderDelegates[i].Execute(InCommandList));
		}
	}
	TSharedPtr<FExtender> MenuExtender = FExtender::Combine(Extenders);

	const bool bShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, InCommandList, MenuExtender);

	MenuBuilder.BeginSection("ProjectSettingsSection", LOCTEXT("ProjectSettings", "Game Specific Settings"));
	{
		MenuBuilder.AddMenuEntry(PresentationEditorCommands::Get().NewSlide);
		MenuBuilder.AddMenuEntry(PresentationEditorCommands::Get().NewCustomDesign);
		MenuBuilder.AddMenuEntry(PresentationEditorCommands::Get().ConfigureButton);
		MenuBuilder.AddMenuEntry(PresentationEditorCommands::Get().ToolsButton);
	}
	MenuBuilder.EndSection();

#undef LOCTEXT_NAMESPACE

	return MenuBuilder.MakeWidget();
}

void PresentationEditorModule::BindCommands()
{
	pluginCommands = MakeShareable(new FUICommandList);

	pluginCommands->MapAction(
		PresentationEditorCommands::Get().ToolsButton,
		FExecuteAction::CreateStatic(&PresentationEditorCommands::OpenPresentationTools_Clicked));

	pluginCommands->MapAction(
		PresentationEditorCommands::Get().NewSlide,
		FExecuteAction::CreateStatic(&PresentationEditorCommands::NewSlide_Clicked));

	pluginCommands->MapAction(
		PresentationEditorCommands::Get().ConfigureButton,
		FExecuteAction::CreateStatic(&PresentationEditorCommands::ConfigurePresentation_Clicked));

	pluginCommands->MapAction(
		PresentationEditorCommands::Get().NewCustomDesign,
		FExecuteAction::CreateStatic(&PresentationEditorCommands::NewCustomDesign_Clicked));
}

IMPLEMENT_MODULE(PresentationEditorModule, PresentationEditorModule)

#endif
