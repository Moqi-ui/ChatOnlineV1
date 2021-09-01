// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGmeMode.h"
#include "LoginHUD.h"
#include "LoginPawn.h"

ALoginGmeMode::ALoginGmeMode()
{
	HUDClass = ALoginHUD::StaticClass();
	DefaultPawnClass = ALoginPawn::StaticClass();

}

void ALoginGmeMode::BeginPlay()
{
	Super::BeginPlay();

}

void ALoginGmeMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}