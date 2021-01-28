// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <time.h>
#include "auth_buffer.h"
#include "tmg_sdk.h"
#include "BaseVoiceControlSystem.generated.h"

using namespace std;
class ALevelScriptActorRoom;
/**
 * 
 */

enum PttState {
	PttState_None = 0,
	PttState_Recording,
	PttState_Playing,
	PttState_Uploading,
	PttState_Downloading,
	PttState_ToTexting,
};

#if PLATFORM_PS4 || PLATFORM_XBOXONE
enum EActiveWidget
{
	Home,
	OutRoom,
	Room,
	Ptt
};
enum EKeyEvent
{
	Up,
	Down,
	Right,
	Left,
	Enter,
	EnterRelease
};
#endif

UCLASS()
class CHATONLINE_WFY_API UBaseVoiceControlSystem : public UObject, public ITMGDelegate
{
	GENERATED_BODY()

public:

	UBaseVoiceControlSystem();

	virtual ~UBaseVoiceControlSystem();

	virtual bool Create(ALevelScriptActorRoom* pActor) { return false; }

	virtual void Destory() {}

	virtual void Show(bool bShow) {}

	virtual void UpdateTips();

	virtual void UpdatePosition();

	virtual void OnEvent(ITMG_MAIN_EVENT_TYPE eventType, const char* data);

	static std::string getFilePath();

#if PLATFORM_PS4 || PLATFORM_XBOXONE
	virtual void OnKeyEvent(const EKeyEvent keyEvnet) {}
#endif


protected:
	int InitGME(std::string sdkAppId, std::string sdkAppKey, std::string userId);
	void EnterRoom(std::string roomID, ITMG_ROOM_TYPE roomType);
	void OnEndpointsUpdateInfo(int32 eventID, const char* identifier);
	void OnClickChangeDemo();


protected:
	virtual void SetPositionInfo(FString positionInfo) {}
	virtual void SetTips(std::string tips) {}
	virtual int GetRange() { return 10000; }
	virtual void onEnterRoomCompleted(int32 result, FString errInfo) {}
	virtual void onExitRoomCompleted(int32 result, FString errInfo);
	virtual void onPttRecordFileCompleted(int32 result, FString filePath, int duration, int filesize) {}
	virtual void onPttPlayFileCompleted(int32 result, FString filePath) {}
	virtual void onPttUploadFileCompleted(int32 result, FString filePath, FString fileID) {}
	virtual void onPttDownloadFileCompleted(int32 result, FString filePath, FString fileID) {}
	virtual void onPttSpeech2TextCompleted(int32 result, FString fileID, FString text) {}
	virtual void onPttStreamRecognitionCompleted(int32 result, FString filePath, FString fileID, FString text) {}

	virtual void onPttStreamRecognitionisRunning(int32 result, FString filePath, FString fileID, FString text) {}



protected:
	ALevelScriptActorRoom* m_pActor;
	bool m_isCreated;
	bool m_isEnableTips;
	int m_tipsMark;
	std::string m_appId;
	std::string m_appKey;
	std::string m_userId;

private:
	std::map<std::string, FVector> identifierList;
	std::map<std::string, pair<AActor*, AActor*>> actorList;
	int m_ClickCount;
	time_t m_FirstClickTime;

//protected:
//
//	int InitGME(std::string sdkAppId, std::string sdkAppKey, std::string OpenId);
//
//	void EnterRoom(std::string roomId, ITMG_ROOM_TYPE roomType);


	
//
//protected:
//
//	std::string m_appId;
//	std::string m_appKey;
//	std::string m_userId;

};
