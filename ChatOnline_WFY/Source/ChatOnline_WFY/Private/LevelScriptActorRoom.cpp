// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptActorRoom.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "tmg_sdk.h"
#include "VoiceControlSystem.h"

ALevelScriptActorRoom::ALevelScriptActorRoom()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelScriptActorRoom::BeginPlay() {
	Super::BeginPlay();

	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("BeginPlay"));

	myVoiceControlSystem = NewObject<UVoiceControlSystem>();

	if (myVoiceControlSystem)
	{
		myVoiceControlSystem->OnInitGME();

		myVoiceControlSystem->OnEnterRoom("202101");

		//myVoiceControlSystem->onCheckMic(true);

		//myVoiceControlSystem->onCheckSpeaker(true);

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("myVoiceControlSystem"));
	}
}

void ALevelScriptActorRoom::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	ITMGContextGetInstance()->Poll();
}

void ALevelScriptActorRoom::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	ITMGContextGetInstance()->Uninit();
}


