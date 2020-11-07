// Fill out your copyright notice in the Description page of Project Settings.


#include "SQTile.h"
#include "Materials/MaterialInstanceConstant.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Match3vDrawLineGameModeBase.h"

ASQTile::ASQTile()
{
	MyGM = nullptr;
	GridAddressX = 0;
	GridAddressY = 0;
}

// Called when the game starts or when spawned
void ASQTile::BeginPlay()
{
	Super::BeginPlay();

	OrgScaleValue = this->GetActorScale3D();

	MyGM = Cast<AMatch3vDrawLineGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	OnClicked.AddDynamic(this, &ASQTile::SelectTile);
	//OnBeginCursorOver.AddDynamic(this, &ASQTile::MouseOverTile);
}

void ASQTile::SetGridAddress(int32 Row, int32 Column)
{
	GridAddressX = Row;
	GridAddressY = Column;
}

void ASQTile::SetTileMaterial(class UMaterialInstanceConstant* MaterialToUse)
{
	GetRenderComponent()->SetMaterial(0, MaterialToUse);
}

void ASQTile::SelectTile(AActor* TouchedActor, FKey ButtonPressed)
{
	this->SetActorScale3D(NewScaleValue);
	MyGM->CreateTileSelection(TouchedActor);
}

void ASQTile::MouseOverTile()
{
}

void ASQTile::ResetScale()
{
	this->SetActorScale3D(OrgScaleValue);
}
