// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceControlSystem.h"
#include "Engine/Engine.h"
#include "time.h"

using namespace std;

void UVoiceControlSystem::OnInitGME()
{
	int ret = InitGME();

	ITMGContextGetInstance()->SetAdvanceParams("SetStreamingRecTimeOut", "5");
	FString msg = FString::Printf(TEXT("onLogin ret=%d"), ret);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, msg);

	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.0f, FColor::Green, "strAppId:" + strAppId);
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.0f, FColor::Green, "strKey:" + strKey);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.0f, FColor::Green, "strUserId:" + strUserId);
}

void UVoiceControlSystem::OnEnterRoom(FString roomId)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onEnterRoom"));
	std::string strRoomID = TCHAR_TO_UTF8(*roomId);

	EnterRoom(roomId,(ITMG_ROOM_TYPE)0);
}

void UVoiceControlSystem::OnExitRoom()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onExitRoom"));
	ITMGContextGetInstance()->ExitRoom();
}

void UVoiceControlSystem::onCheckMic(bool isChecked)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckMic"));
	ITMGContextGetInstance()->GetAudioCtrl()->EnableMic(isChecked);
}

void UVoiceControlSystem::onCheckSpeaker(bool isChecked)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckSpeaker"));
	ITMGContextGetInstance()->GetAudioCtrl()->EnableSpeaker(isChecked);
}

void UVoiceControlSystem::EarToReturn(bool icChecked)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckEarToReturn"));
	ITMGContextGetInstance()->GetAudioCtrl()->EnableLoopBack(icChecked);
}