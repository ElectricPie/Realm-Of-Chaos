// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPointListWidget.h"

#include "Components/VerticalBox.h"
#include "Ui/ExtractionPointWidget.h"

void UExtractionPointListWidget::AddExtractionPoint(const FText& Name, const int32 Distance)
{
	if (!ExtractionPointWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionPointWidgetClass is null"));
		return;
	}
	if (!ExtractionPointList)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionPointList is null"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Point Added"));
	
	UExtractionPointWidget* ExtractionPointWidget = CreateWidget<UExtractionPointWidget>(this, ExtractionPointWidgetClass);
	ExtractionPointWidget->SetPointName(Name);
	ExtractionPointWidget->SetPointDistance(Distance);
	ExtractionPointWidgets.Add(ExtractionPointWidget);
	ExtractionPointList->AddChild(ExtractionPointWidget);
}