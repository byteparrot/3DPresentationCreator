
#pragma once

#if WITH_EDITOR

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "MultiBoxExtender.h"
#include "SDockTab.h"
#include "WorkflowTabManager.h"

class FSpawnTabArgs;

/**
* The public interface to this module.  In most cases, this interface is only public to sibling modules
* within this plugin.
*/
class PresentationEditorModule : public IModuleInterface
{
private:
	/**
	* AddToolbarExtension adds the "New Slide" Button and the "PresentationTools" Drop Down Menu to the
	* Unreal Engine Toolbar which normally resides at the top of the Editor
	*
	* @param builder FToolBarBuilder is used to build the toolbar buttons and combo buttons
	*/
	void AddToolbarExtension(FToolBarBuilder& builder) const;
	
	/**
	* BindCommands binds the commands to the correct buttons inside the toolbar and the dropdown menu
	*/
	void BindCommands();

	TSharedRef<SDockTab> presentationTab(const FSpawnTabArgs& TabSpawnArgs) const;	// the presentation tab
	TSharedPtr<FUICommandList> pluginCommands;					// the commands of the plugin (commands that are executed from the plugin buttons
	TSharedPtr<FExtensibilityManager> extensibilityManager;		// extensibilitymanager used to register toolbar extension
	TSharedPtr<FExtender> toolbarExtender;						// toolbar extender to add the buttons to the toolbar

	/**
	* GeneratePresentationSettingsMenu generates the presentation settings menu when pressing the combo button
	*
	* @param InCommandList are the commands that are mapped to the buttons of the drop down menu
	* @return SWidget that represents the DropDownMenu
	*/
	static TSharedRef< SWidget > GeneratePresentationSettingsDropDownMenu(TSharedRef<FUICommandList> InCommandList);

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.

	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline PresentationEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<PresentationEditorModule>("PresentationEditorModule");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("PresentationEditorModule");
	}
};

#endif