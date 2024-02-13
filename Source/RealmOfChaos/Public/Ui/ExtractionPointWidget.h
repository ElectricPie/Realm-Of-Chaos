// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionPointWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UExtractionPointWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* PointNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* PointDistanceText;
};
