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

	//Creating pointers to ASQTile class to help find adjoing tiles
	class ASQTile* LastSelectedTile;
	class ASQTile* CurrentTile;


	//Variables to store the current grid width and height
	int32 GridWidth;
	int32 GridHeight;

	//Variable which defines the minimum selection required to make a match fetched from Grid
	int32 iMinMatchNumber;

	//Set to true if the tile is adjacent to the last selected tile
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

	//Array to store the selection of tiles upto the minimum selection specified
	TArray<ASQTile*> ArrSelectedTiles;

	//Function that handles the Tile Checks for Match
	UFUNCTION()
	void CreateTileSelection(AActor* TouchedActor);

	//Function to clear the Array as Match Check has failed
	UFUNCTION()
	void ClearTileSelection();

	//Function to add new tile to array as Adjoing element check is Validated
	UFUNCTION()
	void AddTileSelection();

	//Function to return total score to the widget for display
	UFUNCTION(BlueprintPure)
	int32 ReturnScore();
};
