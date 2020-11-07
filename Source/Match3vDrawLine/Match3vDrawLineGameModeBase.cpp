// Copyright Epic Games, Inc. All Rights Reserved.


#include "Match3vDrawLineGameModeBase.h"
#include "SQTile.h"
#include "BaseGrid.h"
#include "Kismet/GameplayStatics.h"

AMatch3vDrawLineGameModeBase::AMatch3vDrawLineGameModeBase()
{
	LastSelectedTile = nullptr;
	CurrentTile = nullptr;

	//Grid default values
	GridWidth = 0;
	GridHeight = 0;

	//Setting the minimum number of match required to be 0
	iMinMatchNumber = 0;

	//Setting the selection array to be empty
	ArrSelectedTiles.Empty();

	//Setting the bool to false indicating that current no adjacent members found
	bIsAdjacent = false;

}

// Called when the game starts or when spawned
void AMatch3vDrawLineGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Setting score to 0
	TotalScore = 0;

	//Findind the existing grid in the project and getting their width and height dimensions
	TArray<AActor*>FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseGrid::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		MyGrid = Cast<ABaseGrid>(FoundActors[0]);
		GridWidth = MyGrid->iGridWidth;
		GridHeight = MyGrid->iGridHeight;
		iMinMatchNumber = MyGrid->iMinMatchNumber;
	}
}

void AMatch3vDrawLineGameModeBase::CreateTileSelection(AActor* TouchedActor)
{
	//Checking whether the touched item is an Tile 
	CurrentTile = Cast<ASQTile>(TouchedActor);
	if (CurrentTile != nullptr)
	{
		//Checking if the selection is a new one
		if ((LastSelectedTile != nullptr) && (LastSelectedTile != CurrentTile))
		{
			//Checking if the selected tile has already been preselected and added to array
			bool IsPreselected = false;
			for (int i = 0; i < ArrSelectedTiles.Num(); i++)
			{
				if (CurrentTile == ArrSelectedTiles[i])
				{
					ClearTileSelection();
					IsPreselected = true;
					break;
				}
			}
			//Executed when the selected item is unique and does not exist in array
			if (IsPreselected != true)
			{
				//Check if the selected items are of the same type or not
				if (LastSelectedTile->SQTileTypeID == CurrentTile->SQTileTypeID)
				{
					//Setting bool to false stating that current no tile is adjacent
					bIsAdjacent = false;

					//Check if the new tile is adjacent to the existing selected tile
					if (((LastSelectedTile->GridAddressX + 1) == CurrentTile->GridAddressX) && (LastSelectedTile->GridAddressY == CurrentTile->GridAddressY))
					{
						bIsAdjacent = true;
					}
					else if (((LastSelectedTile->GridAddressX - 1) == CurrentTile->GridAddressX) && (LastSelectedTile->GridAddressY == CurrentTile->GridAddressY))
					{
						bIsAdjacent = true;
					}
					else if ((LastSelectedTile->GridAddressX == CurrentTile->GridAddressX) && ((LastSelectedTile->GridAddressY + 1) == CurrentTile->GridAddressY))
					{
						bIsAdjacent = true;
					}
					else if ((LastSelectedTile->GridAddressX == CurrentTile->GridAddressX) && ((LastSelectedTile->GridAddressY - 1) == CurrentTile->GridAddressY))
					{
						bIsAdjacent = true;
					}
					else
					{
						bIsAdjacent = false;
					}

					//If found adjacent then add to array
					if (bIsAdjacent)
					{
						AddTileSelection();
						if (ArrSelectedTiles.Num() == iMinMatchNumber)
						{
							for (int32 i = 0; i < ArrSelectedTiles.Num(); i++)
							{
								ArrSelectedTiles[i]->Destroy();
							}
							TotalScore += MyGrid->SQTileLibrary[LastSelectedTile->SQTileTypeID].Points * iMinMatchNumber;
							ClearTileSelection();
						}
					}
					else
					{
						ClearTileSelection();
					}

				}
				else
				{
					ClearTileSelection();
				}
			}

		}
		//Checking whether the selected item is again selected
		else if (LastSelectedTile == CurrentTile)
		{
			ClearTileSelection();
		}
		else
		{
			AddTileSelection();
		}
	}
}

void AMatch3vDrawLineGameModeBase::ClearTileSelection()
{
	for (int i = 0; i < ArrSelectedTiles.Num(); i++)
	{
		ArrSelectedTiles[i]->ResetScale();
	}

	LastSelectedTile->ResetScale();
	CurrentTile->ResetScale();

	LastSelectedTile = nullptr;
	CurrentTile = nullptr;
	ArrSelectedTiles.Empty();
}

void AMatch3vDrawLineGameModeBase::AddTileSelection()
{
	ArrSelectedTiles.Add(CurrentTile);
	LastSelectedTile = CurrentTile;
}

int32 AMatch3vDrawLineGameModeBase::ReturnScore()
{
	return TotalScore;
}
