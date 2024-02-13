// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/ExtractionPointWidget.h"

#include "Components/TextBlock.h"

void UExtractionPointWidget::SetPointName(const FText& Text) const
{
	if (PointNameText)
	{
		PointNameText->SetText(Text);
	}
}

void UExtractionPointWidget::SetPointDistance(const int32 Distance) const
{
	if (PointDistanceText)
	{
		PointDistanceText->SetText(FText::FromString(FString::FromInt(Distance)));
	}
}