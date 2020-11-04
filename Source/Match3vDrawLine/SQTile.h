// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "SQTile.generated.h"

/**
 * 
 */
UCLASS()
class MATCH3VDRAWLINE_API ASQTile : public APaperSpriteActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category = "Tile")
	int32 GridAddressX;

	UPROPERTY(VisibleDefaultsOnly, Category = "Tile")
	int32 GridAddressY;

	UPROPERTY(BlueprintReadOnly)
	int32 SQTileTypeID;

	UFUNCTION(BlueprintCallable)
	void SetGridAddress(FVector SpawnLocation);

	
};
