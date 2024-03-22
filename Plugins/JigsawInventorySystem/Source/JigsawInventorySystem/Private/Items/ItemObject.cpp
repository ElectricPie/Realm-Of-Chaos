// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemObject.h"

FIntPoint UItemObject::GetSize() const
{
	if (bIsRotated)
	{
		return FIntPoint(Size.Y, Size.X);
	}
	
	return Size;
}

UMaterialInterface* UItemObject::GetIcon() const
{
	if (bIsRotated)
	{
		return IconRotated;
	}
	
	return Icon;
}

void UItemObject::Rotate()
{
	bIsRotated = !bIsRotated;
}
