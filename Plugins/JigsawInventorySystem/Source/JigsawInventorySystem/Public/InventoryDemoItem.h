// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class JIGSAWINVENTORYSYSTEM_API FInventoryDemoItem
{
public:
	FInventoryDemoItem();
	FInventoryDemoItem(FName Name, FString Description, int32 Value);
	~FInventoryDemoItem();

private:
	FName ItemName;
	FString Description;
	int32 Value;
};
