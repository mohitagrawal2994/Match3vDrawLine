// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrid.generated.h"

USTRUCT(BlueprintType)
struct FSQTileType
{
	GENERATED_USTRUCT_BODY();

	//Member to set the tile texture
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	class UMaterialInstanceConstant* SQTileMaterial = nullptr;

	//Member to set the tile property like is it movable or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TSubclassOf<class ASQTile> SQTileClass;
};


UCLASS()
class MATCH3VDRAWLINE_API ABaseGrid : public AActor
{
	GENERATED_BODY()

	//Define the value based on which the offset is applied to spawn the sprite sheet
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int32 OffsetValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABaseGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//StaticMesh that holds the backround material
	UPROPERTY(EditDefaultsOnly, Category = "Background")
	class UStaticMeshComponent* MyBG;

	//Minimum number of matching tiles required
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	int32 iMinimumMatchNumber;

	//The width of the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	int32 iGridWidth;

	//The height of the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	int32 iGridHeight;

	//List to save the spawned tiles with location
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASQTile*> ArrGameTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSQTileType> SQTileLibrary;

	//Funtion to spawn the default members of the grid
	void InitializeGrid();

	//Function to get the type of tile to spawn
	int32 GetTileID();

	//Function to spawn Tiles
	void SpawnSQTiles(FVector SpawnLocation, int32 CurrentTileID);

};
