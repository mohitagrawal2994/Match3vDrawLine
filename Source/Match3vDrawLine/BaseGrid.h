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

	//Used to set the scale of the SpriteActor when the object is selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	FVector ScaleValue = FVector(1.0f, 1.0f, 1.0f);

	//Property to set the amount of points to add when a match is found
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int32 Points;

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

	//StaticMesh that holds the backround
	UPROPERTY(EditDefaultsOnly, Category = "Background")
	class UStaticMeshComponent* MyBG;

	//The width of the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 iGridWidth;

	//The height of the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 iGridHeight;

	//Variable which defines the minimum selection required to make a match
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 iMinMatchNumber;

	//Array to hold a list of type of tiles to be spawned on the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSQTileType> SQTileLibrary;

	//Funtion to spawn the default members of the grid
	void InitializeGrid();

	//Function to get the type of tile to spawn
	int32 GetTileID();

	//Function to spawn the Tiles Instances
	void SpawnSQTiles(FVector SpawnLocation, int32 CurrentTileID, int32 Row, int32 Column);

};
