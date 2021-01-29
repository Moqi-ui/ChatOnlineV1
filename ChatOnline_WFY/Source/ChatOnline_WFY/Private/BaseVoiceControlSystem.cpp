// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVoiceControlSystem.h"
#include "Kismet/GameplayStatics.h"
#include "LevelScriptActorRoom.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Engine.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
#include "JsonObject.h"

int scaleSize = 8;

UBaseVoiceControlSystem::UBaseVoiceControlSystem()
{

}

UBaseVoiceControlSystem::~UBaseVoiceControlSystem()
{
	
}

int UBaseVoiceControlSystem::InitGME(std::string sdkAppId, std::string sdkAppKey, std::string OpenId)
{
	//初始化sdk   by Mr-cao 20201126
	int nAppId = atoi(sdkAppId.c_str());
	int ret = ITMGContextGetInstance()->Init(sdkAppId.c_str(), OpenId.c_str());
	ITMGContextGetInstance()->SetTMGDelegate(this);

	//检查麦克风许可
	int RetCode = (int)ITMGContextGetInstance()->CheckMicPermission();
	FString mag = FString::Printf(TEXT("check Permission retcode = %d"), RetCode);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *mag);

	char strSig[128] = { 0 };
	unsigned int nLength = 128;
	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppId, "0", OpenId.c_str(), sdkAppKey.c_str(), (unsigned char*)strSig, nLength);
	ITMGContextGetInstance()->GetPTT()->ApplyPTTAuthbuffer(strSig, nLength);
	ITMGContextGetInstance()->SetAdvanceParams("ForceHighQuanlityState", "0");

	m_appId = sdkAppId;
	m_appKey = sdkAppKey;
	m_userId = OpenId;

	return ret;
}

void UBaseVoiceControlSystem::EnterRoom(std::string roomId, ITMG_ROOM_TYPE roomType)
{
	int nAppId = atoi(m_appId.c_str());

	char strSig[128] = { 0 };
	unsigned int nLength = 128;
	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppId, roomId.c_str(), m_userId.c_str(), m_appKey.c_str(), (unsigned char*)strSig, nLength);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnEnterRoom"));
	ITMGContextGetInstance()->EnterRoom(roomId.c_str(), roomType, strSig, nLength);
}

void UBaseVoiceControlSystem::OnEvent(ITMG_MAIN_EVENT_TYPE eventType, const char* data)
{
	FString jsonData = FString(UTF8_TO_TCHAR(data));
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FString(UTF8_TO_TCHAR(data)));
	FJsonSerializer::Deserialize(Reader, JsonObject);


	if (eventType == ITMG_MAIN_EVENT_TYPE_ENTER_ROOM) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString error_info = JsonObject->GetStringField(TEXT("error_info"));
		if (result == 0) {
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, TEXT("Enter room success."));
		}
		else {
			FString msg = FString::Printf(TEXT("Enter room failed. result=%d, info = %ls"), result, *error_info);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, *msg);
		}
		//onEnterRoomCompleted(result, error_info);
	}
}
