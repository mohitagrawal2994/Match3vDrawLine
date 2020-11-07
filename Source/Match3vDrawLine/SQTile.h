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

class AMatch3vDrawLineGameModeBase* MyGM;

public:
	//Constructor
	ASQTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Tile")
	int32 GridAddressX;

	UPROPERTY(BlueprintReadOnly, Category = "Tile")
	int32 GridAddressY;

	UPROPERTY(BlueprintReadOnly)
	int32 SQTileTypeID;

	UPROPERTY(BlueprintReadOnly)
	FVector NewScaleValue;

	UPROPERTY(BlueprintReadOnly)
	FVector OrgScaleValue;

	UFUNCTION()
	void SetGridAddress(int32 Row, int32 Column);

	UFUNCTION()
	void SetTileMaterial(class UMaterialInstanceConstant* TileMaterial);

	//This function is called when a particular tile is selected
	UFUNCTION()
	void SelectTile(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	void MouseOverTile();

	UFUNCTION()
	void ResetScale();

};
