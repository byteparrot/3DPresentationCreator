// Fill out your copyright notice in the Description page of Project Settings.

#include "PresentationRuntimeModulePCH.h"
#include "PresentationGameMode.h"


APresentationGameMode::APresentationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/PresentationPlugin/PresentationPawnBP"));
	if (PlayerPawnClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClass.Class;
	}

}
