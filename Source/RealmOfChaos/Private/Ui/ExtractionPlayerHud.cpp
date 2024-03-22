// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPlayerHud.h"

#include "Ui/ExtractionPlayerHudWidget.h"

void AExtractionPlayerHud::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AExtractionPlayerHud::BeginPlay"));
	
	// Setup Ui
	if (ExtractionHudClass)
	{
		Hud = CreateWidget<UExtractionPlayerHudWidget>(GetOwningPlayerController(), ExtractionHudClass);
		Hud->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionHudClass is not set in %s"), *GetName());
	}
}
