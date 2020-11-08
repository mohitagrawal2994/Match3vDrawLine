// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

// Called when the game starts or when spawned
void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//To Show mouse during gameplay and to enable its Clickc during game
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}