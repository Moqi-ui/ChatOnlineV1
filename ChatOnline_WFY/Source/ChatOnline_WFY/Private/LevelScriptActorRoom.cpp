// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptActorRoom.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "tmg_sdk.h"

ALevelScriptActorRoom::ALevelScriptActorRoom()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelScriptActorRoom::BeginPlay() {
	Super::BeginPlay();

	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("BeginPlay"));
}

void ALevelScriptActorRoom::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	ITMGContextGetInstance()->Poll();
}

void ALevelScriptActorRoom::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	ITMGContextGetInstance()->Uninit();
}


