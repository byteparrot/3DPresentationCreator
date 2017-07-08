#pragma once

#include "PresentationEditorModulePCH.h"
#include "Slide.h"
#include "PresentationGameMode.h"
#include "Programs/UnrealHeaderTool/Private/ParserClass.h"
#include "Programs/UnrealHeaderTool/Private/Classes.h"

/**
* PluginManager implements the singleton pattern and is reachable from anywhere inside the plugin
*/
class PluginManager
{
private:
	PluginManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ASlide> slideBPClass;	// stores the blueprint class of the slides (for spawning)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class APresentationGameMode> gameModeClass; // stores the blueprint class of the gamemode (for configuring presentation mode)

public:

	/**
	* getInstance returns the instance of the PluginManager
	* if it hasnt been created yet it will be created in here
	*/
	static PluginManager* getInstance()
	{
		return (!instance) ? instance = new PluginManager() : instance;
	}
	static PluginManager* instance;

	PluginManager(PluginManager const&) = delete;
	void operator=(PluginManager const&) = delete;

	/**
	* spawnSlide spawns a slide of the before set slideBPClass in the world at the camera location
	* @param World is the gameworld in which the slide has to be created
	*/
	void spawnSlide(UWorld* const World) const;

	/**
	* printMessageBox prints a messae inside a small box on the right side of the editor
	* to tell the user that something happened
	* @param &InText is the text that should be printed inside the box
	*/
	static void printMessageBox(const FText &InText);

	void setGameModeClass(TSubclassOf<APresentationGameMode> gameModeClass)
	{
		this->gameModeClass = gameModeClass;
	}
	
	void setSlideBPClass(TSubclassOf<AActor> slideBPClass)
	{
		this->slideBPClass = slideBPClass;
	}

	TSubclassOf<class ASlide> getSlideBPClass() const
	{
		return this->slideBPClass;
	}

	TSubclassOf<class APresentationGameMode> getGameModeClass() const
	{
		return this->gameModeClass;
	}


};
