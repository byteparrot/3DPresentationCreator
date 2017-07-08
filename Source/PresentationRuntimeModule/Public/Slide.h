// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Slide.generated.h"

/**
* Slide is the actor that represents a Slide in the gameworld - this class is derived by the blueprint class SlideBP
*/
UCLASS()
class PRESENTATIONRUNTIMEMODULE_API ASlide : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlide();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SlideIndex = -1;	// index of the slide in the presentation

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Is called everytime a property changes like when the user changes the text of a slide
	* @param PropertyChangedEvent is the event that caused the change
	*/
	void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent);

	/**
	* getViewportSize returns the current size of the viewport inside the editor and inside
	* the packaged presentation to adapt the slide size to it
	* @return size as a 2d vector
	*/
	UFUNCTION(BlueprintCallable)
	FVector2D getViewportSize();

	/**
	* GetLastSlideNumber returns the last slide index in the presentation
	* @return integer which represents the last slide index
	*/
	UFUNCTION(BlueprintCallable)
	static int GetLastSlideNumber();

	/**
	* FixSlideNumbers runs through every slide and fixes the slide index if a missing index was detected
	*/
	UFUNCTION(BlueprintCallable)
	static void FixSlideNumbers();
};

