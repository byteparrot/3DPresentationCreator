#include "PresentationRuntimeModulePCH.h"

#include "Modules/ModuleManager.h"
#include "PresentationRuntimeModule.h"
#include "Engine.h"


DEFINE_LOG_CATEGORY(PresentationPluginRuntimeLog)

void PresentationRuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	UE_LOG(PresentationPluginRuntimeLog, Log, TEXT("Starting Runtime logic"));

}


void PresentationRuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

IMPLEMENT_MODULE(PresentationRuntimeModule, PresentationRuntimeModule)
