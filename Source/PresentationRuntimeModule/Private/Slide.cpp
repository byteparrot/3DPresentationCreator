// Fill out your copyright notice in the Description page of Project Settings.

#include "PresentationRuntimeModulePCH.h"

#if WITH_EDITOR
#include "UnrealEd.h"
#endif
#include "Slide.h"


// Sets default values
ASlide::ASlide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASlide::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASlide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void ASlide::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	if(this != this->GetClass()->GetDefaultObject())
		this->RerunConstructionScripts();
	UE_LOG(PresentationPluginRuntimeLog, Log, TEXT("SlidePropertyChanged"));
}
#endif

FVector2D ASlide::getViewportSize()
{
#if WITH_EDITOR
	if (GEditor != nullptr && GEditor->GetActiveViewport() != nullptr) {
		return GEditor->GetActiveViewport()->GetSizeXY();
	}
#endif
	return FIntPoint(1920, 1080);
}

int ASlide::GetLastSlideNumber()
{
#if WITH_EDITOR
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world

	int last = 0;

	for (TObjectIterator<ASlide> Itr; Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != World)
		{
			continue;
		}
		if (Itr->SlideIndex > last)
			last = Itr->SlideIndex;
	}

	return last;
#else
	return 0;
#endif
}

void ASlide::FixSlideNumbers()
{
#if WITH_EDITOR
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world

	int32 min = MAX_int32;
	ASlide* minSlide = nullptr;

	ASlide* tmp = nullptr;

	int last = ASlide::GetLastSlideNumber();

	for (int i = 0; i < last; i++) {

		min = MAX_int32;
		minSlide = nullptr;
		tmp = nullptr;

		for (TActorIterator<ASlide> Itr(World); Itr; ++Itr)
		{
			// Filter out objects not contained in the target world.
			if (Itr->GetWorld() != World)
			{
				continue;
			}

			tmp = *Itr;

			if (Itr->SlideIndex < min && Itr->SlideIndex >= i) {
				min = Itr->SlideIndex;
				minSlide = *Itr;
			}
		}

		if (minSlide)
			minSlide->SlideIndex = i;

	}

#endif
}

