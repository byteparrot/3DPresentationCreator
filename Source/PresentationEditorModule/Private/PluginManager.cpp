#include "PluginManager.h"
#include "UnrealEd.h"
#include "Editor/UnrealEd/Public/EditorViewportClient.h"
#include "Runtime/Slate/Public/Framework/Notifications/NotificationManager.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SNotificationList.h"

PluginManager* PluginManager::instance = nullptr;

PluginManager::PluginManager()
{
	UClass* Result = FindObject<UClass>(ANY_PACKAGE, TEXT("/PresentationPlugin/SlideBP.SlideBP_C"));
	setSlideBPClass(Result);
	setGameModeClass(APresentationGameMode::StaticClass());
}

void PluginManager::spawnSlide(UWorld* const World) const
{

	FEditorViewportClient* client = (FEditorViewportClient*)(GEditor->GetActiveViewport()->GetClient());
	FVector editorCameraDirection = client->GetViewRotation().Vector();
	FVector editorCameraPosition = client->GetViewLocation();

	FVector actorLocation = editorCameraPosition + (editorCameraDirection * 500.0f);
	FRotator actorRotation = FRotationMatrix::MakeFromX(client->GetViewRotation().GetInverse().Add(0, 180, 0).GetInverse().Vector()).Rotator();

	ASlide* newSlide = World->SpawnActor<ASlide>(slideBPClass, actorLocation, actorRotation);

	if(newSlide == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Slide Blueprint not found - Please save & restart the editor with the plugin!"));
	}

	newSlide->SetFolderPath("Slides");

	newSlide->RerunConstructionScripts();

	GEditor->SelectNone(false,true);
	GEditor->SelectActor(newSlide,true,true,true);

}


void PluginManager::printMessageBox(const FText& InText)
{
		FNotificationInfo Info(InText);
		Info.Image = FEditorStyle::GetBrush(TEXT("LevelEditor.RecompileGameCode"));
		Info.FadeInDuration = 0.1f;
		Info.FadeOutDuration = 0.5f;
		Info.ExpireDuration = 1.5f;
		Info.bUseThrobber = false;
		Info.bUseSuccessFailIcons = true;
		Info.bUseLargeFont = true;
		Info.bFireAndForget = false;
		Info.bAllowThrottleWhenFrameRateIsLow = false;
		auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);
		NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
		NotificationItem->ExpireAndFadeout();
}

