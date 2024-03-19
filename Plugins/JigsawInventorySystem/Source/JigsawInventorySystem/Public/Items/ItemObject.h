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
	FIntPoint GetSize() const { return Size; }
	
private:
	UPROPERTY(BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", ExposeOnSpawn))
	FIntPoint Size = FIntPoint(1, 1);
};
