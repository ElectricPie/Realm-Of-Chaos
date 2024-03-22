// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExtractionPlayerHud.generated.h"

class UExtractionPlayerHudWidget;
/**
 * 
 */
UCLASS(HideDropdown)
class REALMOFCHAOS_API AExtractionPlayerHud : public AHUD
{
	GENERATED_BODY()

public:
	UExtractionPlayerHudWidget* GetHud() const { return Hud; }
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UExtractionPlayerHudWidget> ExtractionHudClass;
	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	UExtractionPlayerHudWidget* Hud;
};
