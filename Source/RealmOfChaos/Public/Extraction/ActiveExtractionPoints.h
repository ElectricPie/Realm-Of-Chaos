// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveExtractionPoints.generated.h"

class AExtractionPoint;
/**
 * 
 */
UCLASS(Blueprintable)
class REALMOFCHAOS_API AActiveExtractionPoints : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief Gets a array of Extraction Points which includes the guaranteed points and the ActiveRandomPoints amount
	 * of the furthest points from the start point 
	 * @param StartPoint The point to compare point distanced
	 * @return An array of extraction points
	 */
	TArray<const AExtractionPoint*> GetPointsByDistance(const FVector StartPoint) const;
	
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true", ToolTip="Extraction Points guarented to be accessable to all players"))
	TArray<AExtractionPoint*> GuaranteedPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true", ToolTip="Extraction Points which are randomly chosen for each player"))
	TArray<AExtractionPoint*> RandomPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true", ToolTip="How many random Extraction points are given to each player"))
	int32 ActiveRandomPoints = 1;
};
