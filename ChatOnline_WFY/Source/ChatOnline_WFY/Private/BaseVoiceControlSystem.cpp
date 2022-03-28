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
	//TMGContent = nullptr;
}

UBaseVoiceControlSystem::~UBaseVoiceControlSystem()
{
	
}

int UBaseVoiceControlSystem::InitGME()
{
	srand(time(NULL));
	int uid = rand() % 10000 + 50000;
	UserId = FString::FromInt(uid);

	std::string OpenId = TCHAR_TO_UTF8(*UserId);

	//初始化sdk   by Mr-cao 20201126
	ITMGContext* TMGContent = ITMGContextGetInstance();
	if (TMGContent)
	{
		//int nAppId = atoi(sdkAppId.c_str());
		TMGContent->SetTMGDelegate(this);
		//返回0为初始化成功
		int ret = TMGContent->Init(m_appId.c_str(), OpenId.c_str());

		//检查麦克风许可
		int RetCode = (int)TMGContent->CheckMicPermission();
		FString mag = FString::Printf(TEXT("check Permission retcode = %d"), RetCode);
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *mag);
		if (ret==0)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, "GMEInitSuccess!");

		}
		int nAppId = atoi(m_appId.c_str());
		char strSig[128] = { 0 };
		unsigned int nLength = 128;
		nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppId, "0", OpenId.c_str(), m_appKey.c_str(), (unsigned char*)strSig, nLength);
		TMGContent->GetPTT()->ApplyPTTAuthbuffer(strSig, nLength);
		TMGContent->SetAdvanceParams("ForceHighQuanlityState", "0");
		//TMGContent->SetAdvanceParams("SetStreamingRecTimeOut", "5");
		return ret;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Red, "InitGMEFalid:TMGContent is not valid");
		return 1;
	}
}

void UBaseVoiceControlSystem::EnterRoom(FString roomId_, ITMG_ROOM_TYPE roomType)
{
	std::string roomId = TCHAR_TO_UTF8(*roomId_);

	std::string userId = TCHAR_TO_UTF8(*UserId);

	int nAppId = atoi(m_appId.c_str());

	char strSig[128] = { 0 };

	unsigned int nLength = 128;

	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppId, roomId.c_str(), userId.c_str(), m_appKey.c_str(), (unsigned char*)strSig, nLength);
	
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnEnterRoom"));
	
	ITMGContextGetInstance()->EnterRoom(roomId.c_str(), roomType, strSig, nLength);
}

int UBaseVoiceControlSystem::OnExitRoom()
{
	return ITMGContextGetInstance()->ExitRoom();
}

void UBaseVoiceControlSystem::onCheckMic(bool isChecked)
{
	ITMGContextGetInstance()->GetAudioCtrl()->EnableMic(isChecked);
}

void UBaseVoiceControlSystem::onCheckSpeaker(bool isChecked)
{
	ITMGContextGetInstance()->GetAudioCtrl()->EnableSpeaker(isChecked);
}

int UBaseVoiceControlSystem::GMEGetMicState()
{
	return ITMGContextGetInstance()->GetAudioCtrl()->GetMicState();
}

int UBaseVoiceControlSystem::GMEGetSpeakerState()
{
	return ITMGContextGetInstance()->GetAudioCtrl()->GetSpeakerState();
}

//启用耳返
void UBaseVoiceControlSystem::EarToReturn(bool icChecked)
{
	ITMGContextGetInstance()->GetAudioCtrl()->EnableLoopBack(icChecked);
}

void UBaseVoiceControlSystem::TrySetRangeAudioTeamID(int TeamID)
{
	ITMGContextGetInstance()->SetRangeAudioTeamID(TeamID);

	FString ID = FString::Printf(TEXT("TeamID = %d"), TeamID);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ID);
}

void UBaseVoiceControlSystem::TrySetRangeAudioMode()
{
	ITMGContextGetInstance()->SetRangeAudioMode(ITMG_RANGE_AUDIO_MODE::ITMG_RANGE_AUDIO_MODE_WORLD);
}
void UBaseVoiceControlSystem::UpdatePosition(FVector cameraLocation, FRotator cameraRotation, FString& msg)
{
	ITMGRoom* pTmgRoom = ITMGContextGetInstance()->GetRoom();

	if (!pTmgRoom)
	{
		return;
	}
	pTmgRoom->UpdateAudioRecvRange(1000);

	//FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	//FRotator cameraRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	int position[] = { (int)cameraLocation.X,(int)cameraLocation.Y, (int)cameraLocation.Z };
	FMatrix matrix = ((FRotationMatrix)cameraRotation);
	float forward[] = { matrix.GetColumn(0).X,matrix.GetColumn(1).X,matrix.GetColumn(2).X };
	float right[] = { matrix.GetColumn(0).Y,matrix.GetColumn(1).Y,matrix.GetColumn(2).Y };
	float up[] = { matrix.GetColumn(0).Z,matrix.GetColumn(1).Z,matrix.GetColumn(2).Z };

	pTmgRoom->UpdateSelfPosition(position, forward, right, up);

	msg = FString::Printf(TEXT("location(x=%.2f,y=%.2f,z=%.2f),  rotation(pitch=%.2f,yaw=%.2f,roll=%.2f)"),
		cameraLocation.X, cameraLocation.Y, cameraLocation.Z, cameraRotation.Pitch, cameraRotation.Yaw, cameraRotation.Roll);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, msg);
}


void UBaseVoiceControlSystem::OnEvent(ITMG_MAIN_EVENT_TYPE eventType, const char* data)
{
	FString jsonData = FString(UTF8_TO_TCHAR(data));
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FString(UTF8_TO_TCHAR(data)));
	FJsonSerializer::Deserialize(Reader, JsonObject);

	switch (eventType)
	{
		case ITMG_MAIN_EVENT_TYPE_ENTER_ROOM:
		{
			int32 result = JsonObject->GetIntegerField(TEXT("result"));
			FString error_info = JsonObject->GetStringField(TEXT("error_info"));
			if (result == 0) {
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("Enter room success!!!."));
			}
			else {
				FString msg = FString::Printf(TEXT("Enter room failed. result=%d, info = %ls"), result, *error_info);
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);
			}
			break;
		}
		case ITMG_MAIN_EVENT_TYPE_EXIT_ROOM:
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("Exit room success!!!."));
			break;
		}
		case ITMG_MAIN_EVNET_TYPE_USER_UPDATE:
		{
			int32 eventID = JsonObject->GetIntegerField(TEXT("event_id"));
			TArray<TSharedPtr<FJsonValue>> UserList = JsonObject->GetArrayField(TEXT("user_list"));
			switch (eventID)
			{
				case ITMG_EVENT_ID_USER_ENTER:
				{
					UserUpdateEventId = ITMG_EVENT_ID_USER_ENTER;
					break;
				}
				case ITMG_EVENT_ID_USER_EXIT:
				{
					UserUpdateEventId = ITMG_EVENT_ID_USER_EXIT;
					break;
				}
				case ITMG_EVENT_ID_USER_HAS_AUDIO:
				{
					UserUpdateEventId = ITMG_EVENT_ID_USER_HAS_AUDIO;
					break;
				}
				case ITMG_EVENT_ID_USER_NO_AUDIO:
				{
					//有成员停止发送音频包
					UserUpdateEventId = ITMG_EVENT_ID_USER_NO_AUDIO;
					break;
				}
			}
		}
	}
	//if (eventType == ITMG_MAIN_EVENT_TYPE_ENTER_ROOM) {
	//	
	//	//onEnterRoomCompleted(result, error_info);
	//}
}
