// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtractionPlayerHud.generated.h"

class UExtractionPointListWidget;

/**
 * 
 */
UCLASS()
class REALMOFCHAOS_API UExtractionPlayerHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Extraction", meta=(AllowPrivateAccess="true", BindWidget))
	UExtractionPointListWidget* ExtractionPointListWidget;
	
};
