// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UItemWidget;
class UInventoryComponent;
class USizeBox;
class UCanvasPanel;

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	FLine(): Start(FVector2D::ZeroVector), End(FVector2D::ZeroVector)
	{
	}
	FLine(const FVector2D& Start, const FVector2D& End): Start(Start), End(End)
	{
	}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Line")
	FVector2D Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Line")
	FVector2D End;
};

USTRUCT(BlueprintType)
struct FMousePositionInTile
{
	GENERATED_BODY()

	FMousePositionInTile()
	{
	}

	UPROPERTY(BlueprintReadOnly, Category="Mouse Position")
	bool bIsRight = false;
	UPROPERTY(BlueprintReadOnly, Category="Mouse Position")
	bool bIsDown = false;
};

/**
 * 
 */
UCLASS()
class JIGSAWINVENTORYSYSTEM_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Grid")
	void InitializeGrid(UInventoryComponent* NewInventoryComponent, const float NewTileSize = 50.f);
	UFUNCTION(BlueprintCallable, Category="Grid")
	void Refresh();
	
protected:	
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	USizeBox* GridSizeBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Widgets", meta=(AllowPrivateAccess="true", BindWidget))
	UCanvasPanel* GridCanvasPanel; // Look into alternatives?

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	float TileSize = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	FLinearColor GridLineColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);
	UPROPERTY(BlueprintReadOnly, Category="Grid Drawing", meta=(AllowPrivateAccess="true"))
	TArray<FLine> GridLines;
	
	UPROPERTY(BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Drawing", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UItemWidget> ItemWidgetClass;

	FIntPoint DraggedItemTopLeftTile;
	
	UFUNCTION()
	void OnItemRemoved(UItemObject* RemovedItem);

	FMousePositionInTile MousePositionInTile(const FVector2D MousePosition);
};
