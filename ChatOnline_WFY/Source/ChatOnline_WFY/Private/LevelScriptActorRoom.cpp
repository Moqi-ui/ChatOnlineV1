// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptActorRoom.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
//#include "tmg_sdk.h"
#include "BaseVoiceControlSystem.h"

ALevelScriptActorRoom::ALevelScriptActorRoom()
{
	PrimaryActorTick.bCanEverTick = true;

	//VoiceControlSystem = nullptr;
}

void ALevelScriptActorRoom::BeginPlay() {
	Super::BeginPlay();

	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("BeginPlay"));

	//VoiceControlSystem = NewObject<UBaseVoiceControlSystem>();

	

	//if (VoiceControlSystem)
	//{
	//	FString strAppId = "1400452190";
	//	FString strKey = "U8fTpuA3H0tl4PyI";

	//	srand(time(NULL));
	//	int uid = rand() % 10000 + 50000;
	//	FString strUserId = FString::FromInt(uid);
	//	VoiceControlSystem->InitGME(strAppId, strKey, strUserId);

	//	//VoiceControlSystem->EnterRoom("202102", ITMG_ROOM_TYPE::ITMG_ROOM_TYPE_FLUENCY);

	//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("myVoiceControlSystem"));
	//}
}

void ALevelScriptActorRoom::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

	ITMGContextGetInstance()->Poll();
}

void ALevelScriptActorRoom::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	//VoiceControlSystem = nullptr;
	ITMGContextGetInstance()->Uninit();
}


