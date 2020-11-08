// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGrid.h"
#include "Components/StaticMeshComponent.h"
#include "SQTile.h"

// Sets default values
ABaseGrid::ABaseGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting Default values to the class members
	MyBG = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyBG"));
	RootComponent = MyBG;

	iGridWidth = 6;
	iGridHeight = 7;
	//Setting min match required to 3
	iMinMatchNumber = 3;

	//Setting default spawn offset multiplier
	OffsetValue = 5;

}

// Called when the game starts or when spawned
void ABaseGrid::BeginPlay()
{
	Super::BeginPlay();
	InitializeGrid();
	
}

// Called every frame
void ABaseGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGrid::InitializeGrid()
{
	FVector SpawnLocation;
	FVector BGLocation = MyBG->GetRelativeLocation();
	for (int32 Column = 0; Column < iGridWidth; ++Column)
	{
		for (int32 Row = 0; Row < iGridHeight; ++Row)
		{
			//Getting the type of tile to spawn from the Tile Array
			int32 CurrentTileID =  GetTileID();

			if (CurrentTileID != -1)
			{
				//Setting the spawn location to be from the BG position in X and Y
				SpawnLocation = FVector((BGLocation.X + (Column * OffsetValue)), 0.0f, (BGLocation.Z + (Row * OffsetValue)));
				SpawnSQTiles(SpawnLocation, CurrentTileID, Row, Column);
			}
			
		}
	}
}

int32 ABaseGrid::GetTileID()
{
	if (SQTileLibrary.Num() <= 0)
	{
		return -1;
	}
	int32 GeneratedTileID = int32(FMath::FRandRange(0, SQTileLibrary.Num()));
	return GeneratedTileID;
	
}

void ABaseGrid::SpawnSQTiles(FVector SpawnLocation, int32 CurrentTileID, int32 Row, int32 Column)
{
	// Check for a valid World:
	UWorld* const World = GetWorld();
	if (World)
	{
		// Setting the spawn parameters.
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// Setting The tile Rotation value To 0
		FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
		
		// Spawning the tile.
		ASQTile* const NewSQTile = World->SpawnActor<ASQTile>(SQTileLibrary[CurrentTileID].SQTileClass, SpawnLocation, SpawnRotation, SpawnParams);

		NewSQTile->SQTileTypeID = CurrentTileID;
		NewSQTile->SetGridAddress(Row, Column);
		NewSQTile->SetTileMaterial(SQTileLibrary[CurrentTileID].SQTileMaterial);
		NewSQTile->NewScaleValue = SQTileLibrary[CurrentTileID].ScaleValue;
	}
}