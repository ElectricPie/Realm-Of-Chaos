// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPlayerHud.h"

#include "Extraction/ExtractionPoint.h"
#include "Player/PlayerCharacter.h"
#include "Player/TopDownPlayerController.h"
#include "Ui/ExtractionInventoryWidget.h"
#include "Ui/ExtractionPlayerHudWidget.h"
#include "Ui/ExtractionPointListWidget.h"

void AExtractionPlayerHud::ToggleInventory()
{
	HideAllWidgets();

	if (ActiveWidget == Inventory)
	{
		ActiveWidget = Hud;
		HudWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ActiveWidget = Inventory;
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

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
		// Can't set the visibility here as the inventory needs to be active for the grid to get a size
		InventoryWidget = CreateWidget<UExtractionInventoryWidget>(GetOwningPlayerController(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryWidgetClass is not set in %s"), *GetName());
	}

	// Setup extraction points hud update timer
	GetWorldTimerManager().SetTimer(ExtractionPointsHudUpdateTimer, this,
	                                &AExtractionPlayerHud::UpdateExtractionPointsDistance,
	                                ExtractionPointsHudUpdateInterval, true);

	// Delay to give the inventory widget to have a size
	FTimerHandle DelayedPlayTimerHandle;
	GetWorldTimerManager().SetTimer(DelayedPlayTimerHandle, this, &AExtractionPlayerHud::DelayedOnPlay, DelayedPlayTimer, false);
}

void AExtractionPlayerHud::DelayedOnPlay()
{
	// Needed as the inventory widget can't its size until after it has been active
	if (IsValid(InventoryWidget))
	{
		if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPawn()))
		{
			InventoryWidget->InitializeInventoryWidget(PlayerCharacter);
		}

		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AExtractionPlayerHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AExtractionPlayerHud::UpdateExtractionPointsDistance()
{
	if (UExtractionPointListWidget* ExtractionPointListWidget = HudWidget->GetExtractionPointListWidget())
	{
		if (const ATopDownPlayerController* PlayerController = Cast<ATopDownPlayerController>(
			GetOwningPlayerController()))
		{
			const TArray<const AExtractionPoint*> ExtractionPoints = PlayerController->GetExtractionPoints();
			const FVector PlayerPosition = GetOwningPlayerController()->GetPawn()->GetActorLocation();

			if (bResetExtractionPoints)
			{
				ExtractionPointListWidget->ClearExtractionPoints();
				for (const auto& Point : ExtractionPoints)
				{
					const float DistanceToPoint = FVector::Dist(PlayerPosition, Point->GetActorLocation()) *
						DistanceToExtractionPointModifier;
					ExtractionPointListWidget->AddExtractionPoint(FText::FromName(Point->GetPointName()),
					                                              DistanceToPoint);
				}

				bResetExtractionPoints = false;

				// Dont need to update the points if we just reset them
				return;
			}

			// Update the extraction points list with the new distances
			for (int32 i = 0; i < ExtractionPoints.Num(); ++i)
			{
				const float DistanceToPoint = FVector::Dist(PlayerPosition, ExtractionPoints[i]->GetActorLocation()) *
					DistanceToExtractionPointModifier;
				ExtractionPointListWidget->UpdateExtractionPoint(i, DistanceToPoint);
			}
		}
	}
}

void AExtractionPlayerHud::HideAllWidgets() const
{
	HudWidget->SetVisibility(ESlateVisibility::Collapsed);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
}
