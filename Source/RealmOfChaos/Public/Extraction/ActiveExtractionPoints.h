// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ActiveExtractionPoints.generated.h"

class AExtractionPoint;
/**
 * 
 */
UCLASS(Blueprintable)
class REALMOFCHAOS_API AActiveExtractionPoints : public AInfo
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true", ToolTip="Extraction Points guarented to be accessable to all players"))
	TArray<AExtractionPoint*> GuaranteedPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true", ToolTip="Extraction Points which are randomly chosen for each player"))
	TArray<AExtractionPoint*> RandomPoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Extraction Points", meta=(AllowPrivateAccess="true", ToolTip="How many random Extraction points are given to each player"))
	int32 ActiveRandomPoints = 1;
};
