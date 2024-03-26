// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/InventoryHeaderWidget.h"

#include "Components/TextBlock.h"

void UInventoryHeaderWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(HeaderTextWidget))
	{
		HeaderTextWidget->SetText(HeaderText);
	}
}
