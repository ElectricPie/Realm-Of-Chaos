// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPlayerHud.h"

#include "Extraction/ExtractionPoint.h"
#include "Player/TopDownPlayerController.h"
#include "Ui/ExtractionInventoryWidget.h"
#include "Ui/ExtractionPlayerHudWidget.h"
#include "Ui/ExtractionPointListWidget.h"

void AExtractionPlayerHud::ResetExtractionPoints()
{
	bResetExtractionPoints = true;
}

void AExtractionPlayerHud::BeginPlay()
{
	Super::BeginPlay();
	
	if (ExtractionHudWidgetClass)
	{
		HudWidget = CreateWidget<UExtractionPlayerHudWidget>(GetOwningPlayerController(), ExtractionHudWidgetClass);
		HudWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionHudClass is not set in %s"), *GetName());
	}

	if (IsValid(InventoryWidgetClass))
	{
		InventoryWidget = CreateWidget<UExtractionInventoryWidget>(GetOwningPlayerController(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryWidgetClass is not set in %s"), *GetName());
	}

	// Setup extraction points hud update timer
	GetWorldTimerManager().SetTimer(ExtractionPointsHudUpdateTimer, this, &AExtractionPlayerHud::UpdateExtractionPointsDistance, ExtractionPointsHudUpdateInterval, true);
}

void AExtractionPlayerHud::UpdateExtractionPointsDistance()
{
	if (UExtractionPointListWidget* ExtractionPointListWidget = HudWidget->GetExtractionPointListWidget())
	{
		if (const ATopDownPlayerController* PlayerController = Cast<ATopDownPlayerController>(GetOwningPlayerController()))
		{
			const TArray<const AExtractionPoint*> ExtractionPoints = PlayerController->GetExtractionPoints();
			const FVector PlayerPosition = GetOwningPlayerController()->GetPawn()->GetActorLocation();
			
			if (bResetExtractionPoints)
			{
				ExtractionPointListWidget->ClearExtractionPoints();
				for (const auto& Point : ExtractionPoints)
				{ 
					const float DistanceToPoint = FVector::Dist(PlayerPosition, Point->GetActorLocation()) * DistanceToExtractionPointModifier;
					ExtractionPointListWidget->AddExtractionPoint(FText::FromName(Point->GetPointName()), DistanceToPoint);
				}
			
				bResetExtractionPoints = false;
			
				// Dont need to update the points if we just reset them
				return;
			}
			
			// Update the extraction points list with the new distances
			for (int32 i = 0; i < ExtractionPoints.Num(); ++i)
			{
				const float DistanceToPoint = FVector::Dist(PlayerPosition, ExtractionPoints[i]->GetActorLocation()) * DistanceToExtractionPointModifier;
				ExtractionPointListWidget->UpdateExtractionPoint(i, DistanceToPoint);
			}
		}
	}
}

