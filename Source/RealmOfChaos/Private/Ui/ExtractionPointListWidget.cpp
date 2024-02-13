// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPointListWidget.h"
#include "Ui/ExtractionPointWidget.h"

void UExtractionPointListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TestExtractionPointWidget)
	{
		TestExtractionPointWidget->SetPointName(FText::FromString("Test Point"));
		TestExtractionPointWidget->SetPointDistance(100);
	}
}
