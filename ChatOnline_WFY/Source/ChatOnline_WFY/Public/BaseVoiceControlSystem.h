// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "tmg_sdk.h"
#include "BaseVoiceControlSystem.generated.h"

using namespace std;
/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API UBaseVoiceControlSystem : public UObject, public ITMGDelegate
{
	GENERATED_BODY()

public:

	UBaseVoiceControlSystem();

	virtual ~UBaseVoiceControlSystem();

	virtual void OnEvent(ITMG_MAIN_EVENT_TYPE eventType, const char* data);

public:

	int InitGME();

	void EnterRoom(FString roomId_, ITMG_ROOM_TYPE roomType);

	int OnExitRoom();

	void onCheckMic(bool isChecked);

	void onCheckSpeaker(bool isChecked);

	int GMEGetMicState();

	int GMEGetSpeakerState();

	//ÆôÓÃ¶ú·µ
	void EarToReturn(bool icChecked);


private:

	std::string m_appId = "1400452190";
	std::string m_appKey= "U8fTpuA3H0tl4PyI";
	//std::string m_userId;

	FString UserId;
	
};
