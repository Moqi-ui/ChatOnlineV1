// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatOnLine_GameInstance.h"
//#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void UChatOnLine_GameInstance::Init()
{
	Super::Init();

	Inst_CurrentPlayerNumbers = 0;

	/*UBaseVoiceControlSystem* VoiceControlSystem = NewObject<UBaseVoiceControlSystem>();
	if (VoiceControlSystem)
	{
		srand(time(NULL));
		int uid = rand() % 10000 + 50000;
		UserID = FString::FromInt(uid);
		VoiceControlSystem->InitGME(UserID);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("UChatOnLine_GameInstance::Init()"));
	}*/
}
void UChatOnLine_GameInstance::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	/*if (ITMGContextGetInstance())
	{
		ITMGContextGetInstance()->Poll();
	}*/
	
}

bool UChatOnLine_GameInstance::IsTickable() const
{
	return true;
}

TStatId UChatOnLine_GameInstance::GetStatId() const
{
	return Super::GetStatID();
}

void UChatOnLine_GameInstance::Shutdown()
{
	Super::Shutdown();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("UChatOnLine_GameInstance::Shutdown()"));

	//VoiceControlSystem = nullptr;
	//ITMGContextGetInstance()->Uninit();
}

void UChatOnLine_GameInstance::AddOnePlayerNumbers()
{
	Inst_CurrentPlayerNumbers++;
}

void UChatOnLine_GameInstance::ReduceOnePlayerNumbers()
{
	Inst_CurrentPlayerNumbers--;
}

void UChatOnLine_GameInstance::SetCurrentRoomInfo(FString Key_RoomInfo)
{
	Key_CurrentRoomInfo = Key_RoomInfo;
}
void UChatOnLine_GameInstance::SetUserSpeakerState(bool State)
{
	bUserSpeakState = State;
}

void UChatOnLine_GameInstance::SetUserInfo(FUserInfo userInfo)
{
	CurrentUserInfo = userInfo;
}