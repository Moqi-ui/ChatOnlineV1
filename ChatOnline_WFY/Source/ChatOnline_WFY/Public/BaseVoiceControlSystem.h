// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <tmg_sdk.h>
#include <string>
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

	~UBaseVoiceControlSystem();

protected:

	int InitGME(std::string sdkAppId, std::string sdkAppKey, std::string OpenId);

	void EnterRoom(std::string roomId, ITMG_ROOM_TYPE roomType);

	virtual void OnEvent(ITMG_MAIN_EVENT_TYPE eventType, const char* data);

protected:

	std::string m_appId;
	std::string m_appKey;
	std::string m_userId;

};
