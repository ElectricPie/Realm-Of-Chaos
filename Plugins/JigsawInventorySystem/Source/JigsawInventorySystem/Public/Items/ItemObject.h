// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

class AItemActor;

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class JIGSAWINVENTORYSYSTEM_API UItemObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Item")
	FIntPoint GetSize() const;
	UFUNCTION(BlueprintCallable, Category="Item")
	UMaterialInterface* GetIcon() const;
	UFUNCTION(BlueprintCallable, Category="Item")
	TSubclassOf<AItemActor> GetItemClass() const { return ItemClass; }
	UFUNCTION(BlueprintCallable, Category="Item")
	void Rotate();
	UFUNCTION(BlueprintCallable, Category="Item")
	void SetRotated(const bool bNewIsRotated) { bIsRotated = bNewIsRotated; }

private:
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	FIntPoint Size = FIntPoint(1, 1);
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	UMaterialInterface* Icon;
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	UMaterialInterface* IconRotated;
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	TSubclassOf<AItemActor> ItemClass;
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
	bool bIsRotated = false;
};
