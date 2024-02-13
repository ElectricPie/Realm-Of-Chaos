// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPlayerHud.h"

#include "Ui/ExtractionPointListWidget.h"

void UExtractionPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	// TODO: Debug remove when done
	if (ExtractionPointListWidget != nullptr)
	{
		ExtractionPointListWidget->AddExtractionPoint(FText::FromString("Extraction Point 1"), 100);
		ExtractionPointListWidget->AddExtractionPoint(FText::FromString("Extraction Point 2"), 50);
		ExtractionPointListWidget->AddExtractionPoint(FText::FromString("Extraction Point 3"), 75);
		ExtractionPointListWidget->AddExtractionPoint(FText::FromString("Extraction Point 4"), 170);

		ExtractionPointListWidget->RemoveExtractionPoint(2);
		ExtractionPointListWidget->RemoveExtractionPoint(5);

		ExtractionPointListWidget->UpdateExtractionPoint(1, 25);
		ExtractionPointListWidget->UpdateExtractionPoint(5, 200);
	}
}
