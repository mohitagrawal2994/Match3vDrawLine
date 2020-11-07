// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Match3vDrawLineGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MATCH3VDRAWLINE_API AMatch3vDrawLineGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	class ASQTile* LastSelectedTile;
	class ASQTile* CurrentTile;


	//Variables to store the current grid width and height
	int32 GridWidth;
	int32 GridHeight;

	//Variable which defines the minimum selection required to make a match fetched from Grid
	int32 iMinMatchNumber;
	bool bIsAdjacent;

	//Variable to keep score
	int TotalScore;

	//Variable to store the current grid in level
	class ABaseGrid* MyGrid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public :
	//Constructor
	AMatch3vDrawLineGameModeBase();

	TArray<ASQTile*> ArrSelectedTiles;

	UFUNCTION()
	void CreateTileSelection(AActor* TouchedActor);

	UFUNCTION()
	void ClearTileSelection();

	UFUNCTION()
	void AddTileSelection();
};
