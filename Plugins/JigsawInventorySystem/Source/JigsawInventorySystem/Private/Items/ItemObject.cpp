// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemObject.h"

UMaterialInterface* UItemObject::GetIcon() const
{
	// TODO: Handle rotated icon
	return Icon;
}
