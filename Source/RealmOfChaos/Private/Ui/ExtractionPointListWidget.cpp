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
	
	UExtractionPointWidget* ExtractionPointWidget = CreateWidget<UExtractionPointWidget>(this, ExtractionPointWidgetClass);
	ExtractionPointWidget->SetPointName(Name);
	ExtractionPointWidget->SetPointDistance(Distance);
	ExtractionPointWidgets.Add(ExtractionPointWidget);
	ExtractionPointList->AddChild(ExtractionPointWidget);
}

void UExtractionPointListWidget::RemoveExtractionPoint(const int32 Index)
{
	if (!ExtractionPointList)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionPointList is null"));
		return;
	}
	if (Index < 0 || Index >= ExtractionPointWidgets.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Index out of range"));
		return;
	}

	// Remove the widget from the list and the vertical box
	ExtractionPointList->RemoveChild(ExtractionPointWidgets[Index]);
	ExtractionPointWidgets.RemoveAt(Index);
}

void UExtractionPointListWidget::UpdateExtractionPoint(const int32 Index, const int32 Distance)
{
	if (!ExtractionPointList)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtractionPointList is null"));
		return;
	}
	if (Index < 0 || Index >= ExtractionPointWidgets.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Index out of range"));
		return;
	}

	ExtractionPointWidgets[Index]->SetPointDistance(Distance);
}

void UExtractionPointListWidget::ClearExtractionPoints()
{
	ExtractionPointList->ClearChildren();
	ExtractionPointWidgets.Empty();
}
