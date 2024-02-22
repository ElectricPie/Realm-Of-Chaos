// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDemoItem.h"

FInventoryDemoItem::FInventoryDemoItem()
{
	ItemName = "None";
	Description = "None";
	Value = 0;
}

FInventoryDemoItem::FInventoryDemoItem(const FName Name, const FString Description, const int32 Value): ItemName(Name), Description(Description), Value(Value)
{
}

FInventoryDemoItem::~FInventoryDemoItem()
{
	
}
