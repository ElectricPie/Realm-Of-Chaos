// Fill out your copyright notice in the Description page of Project Settings.


#include "Extraction/ActiveExtractionPoints.h"

#include "Extraction/ExtractionPoint.h"

TArray<const AExtractionPoint*> AActiveExtractionPoints::GetPointsByDistance(const FVector StartPoint) const
{
	TArray<const AExtractionPoint*> ExtractionPoints;
	ExtractionPoints.Append(GuaranteedPoints);

	if (RandomPoints.Num() > 0)
	{
		// Prevent selecting more random points then there are
		int32 RandomPointCount = ActiveRandomPoints;
		if (RandomPoints.Num() < ActiveRandomPoints)
		{
			RandomPointCount = ActiveRandomPoints;
		}

		// Sort the random points by proximity to the start point
		TArray<AExtractionPoint*> SortedPoints;
		SortedPoints.Append(RandomPoints);
		SortedPoints.Sort([StartPoint](const AExtractionPoint& PointA, const AExtractionPoint& PointB)
		{
			return FVector::Dist(StartPoint, PointA.GetActorLocation()) > FVector::Dist(StartPoint, PointB.GetActorLocation());
		});

		// Remove the closer points and add them to the list
		SortedPoints.SetNum(RandomPointCount);
		ExtractionPoints.Append(SortedPoints);
	}

	return ExtractionPoints;
}
