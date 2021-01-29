// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVoiceControlSystem.h"
#include "Kismet/GameplayStatics.h"
#include "LevelScriptActorRoom.h"
#include "Engine/TextRenderActor.h"
#include "UserConfig.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Engine.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
#include "JsonObject.h"

int scaleSize = 8;

UBaseVoiceControlSystem::UBaseVoiceControlSystem()
	: m_pActor(NULL)
	, m_isCreated(false)
	, m_isEnableTips(false)
	, m_tipsMark(0)
	, m_ClickCount(0)
	, m_FirstClickTime(0)
{

}

UBaseVoiceControlSystem::~UBaseVoiceControlSystem()
{
	Destory();
}


int UBaseVoiceControlSystem::InitGME(std::string sdkAppId, std::string sdkAppKey, std::string userId)
{
#ifdef __NX__
	ITMGContextGetInstance()->SetLogPath("gme_log_cache:/GME");
#else
	FString logDir = FPaths::ProjectSavedDir();
	ITMGContextGetInstance()->SetLogPath(TCHAR_TO_UTF8(*logDir));
#endif

	int nAppid = atoi(sdkAppId.c_str());
	int ret = ITMGContextGetInstance()->Init(sdkAppId.c_str(), userId.c_str());
	ITMGContextGetInstance()->SetTMGDelegate(this);

	int RetCode = (int)ITMGContextGetInstance()->CheckMicPermission();
	FString msg = FString::Printf(TEXT("check Permission retcode =%d"), RetCode);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);

	char strSig[128] = { 0 };
	unsigned int nLength = 128;
	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppid, "0", userId.c_str(), sdkAppKey.c_str(), (unsigned char*)strSig, nLength);
	ITMGContextGetInstance()->GetPTT()->ApplyPTTAuthbuffer(strSig, nLength);
	ITMGContextGetInstance()->SetAdvanceParams("ForceHighQuanlityState", "0");
#ifdef ANDROID
	ITMGContextGetInstance()->SetAdvanceParams("LowLatencyOption", "1");
#endif

	m_appId = sdkAppId;
	m_appKey = sdkAppKey;
	m_userId = userId;
	m_isEnableTips = false;
	m_tipsMark = 0;
	return ret;
}

void UBaseVoiceControlSystem::EnterRoom(std::string roomID, ITMG_ROOM_TYPE roomType)
{
	int nAppid = atoi(m_appId.c_str());
	UserConfig::SetRoomID(roomID);

	char strSig[128] = { 0 };
	unsigned int nLength = 128;
	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppid, roomID.c_str(), m_userId.c_str(), m_appKey.c_str(), (unsigned char*)strSig, nLength);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onEnterRoom"));
	ITMGContextGetInstance()->EnterRoom(roomID.c_str(), roomType, strSig, nLength);
}

void UBaseVoiceControlSystem::UpdateTips()
{
	if (!m_isEnableTips || !m_isCreated)
		return;

	if (m_tipsMark >= 30) {
		m_tipsMark = 0;
	}

	if (m_tipsMark == 0) {
		ITMGRoom* pTmgRoom = ITMGContextGetInstance()->GetRoom();
		if (pTmgRoom) {
			static char strSig[1024 * 10] = { 0 };
			std::string NumberOfAudioStreams(ITMGContextGetInstance()->GetAdvanceParams("NumberofAudioStreams"));
			std::string NumberofAllUser(ITMGContextGetInstance()->GetAdvanceParams("NumberofAllUser"));
			std::string NumberofACCUser(ITMGContextGetInstance()->GetAdvanceParams("NumberofACCUser"));
			std::string NumberofProxyUser(ITMGContextGetInstance()->GetAdvanceParams("NumberofProxyUser"));

			const char* tips = pTmgRoom->GetQualityTips();
			if (tips && strlen(tips) > 0)
			{
				sprintf(strSig, "NumberofAudioStreams:%s \n NumberofAllUser:%s  NumberofACCUser:%s   NumberofProxyUser:%s \n %s", NumberOfAudioStreams.c_str(), NumberofAllUser.c_str(), NumberofACCUser.c_str(), NumberofProxyUser.c_str(), tips);
			}
			else
			{
				sprintf(strSig, " ");
			}



			SetTips(strSig);
		}
	}

	m_tipsMark++;
}

void UBaseVoiceControlSystem::UpdatePosition()
{
	if (!m_isCreated)
		return;

	ITMGRoom* pTmgRoom = ITMGContextGetInstance()->GetRoom();
	if (!pTmgRoom)
	{
		return;
	}

	int nRange = GetRange();
	pTmgRoom->UpdateAudioRecvRange(nRange);

	FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(m_pActor->GetWorld(), 0)->GetCameraLocation();
	FRotator cameraRotation = UGameplayStatics::GetPlayerCameraManager(m_pActor->GetWorld(), 0)->GetCameraRotation();

	FString msg = FString::Printf(TEXT("location(x=%.2f,y=%.2f,z=%.2f),  rotation(pitch=%.2f,yaw=%.2f,roll=%.2f)"),
		cameraLocation.X, cameraLocation.Y, cameraLocation.Z, cameraRotation.Pitch, cameraRotation.Yaw, cameraRotation.Roll);

	int position[] = { (int)cameraLocation.X,(int)cameraLocation.Y, (int)cameraLocation.Z };
	FMatrix matrix = ((FRotationMatrix)cameraRotation);
	float forward[] = { matrix.GetColumn(0).X,matrix.GetColumn(1).X,matrix.GetColumn(2).X };
	float right[] = { matrix.GetColumn(0).Y,matrix.GetColumn(1).Y,matrix.GetColumn(2).Y };
	float up[] = { matrix.GetColumn(0).Z,matrix.GetColumn(1).Z,matrix.GetColumn(2).Z };


	pTmgRoom->UpdateSelfPosition(position, forward, right, up);
	SetPositionInfo(msg);
}

std::string UBaseVoiceControlSystem::getFilePath()
{
#if PLATFORM_ANDROID
	extern FString GExternalFilePath;
	FString path = GExternalFilePath + FString("/");
	return TCHAR_TO_UTF8(*path);
#elif PLATFORM_IOS
	char buffer[256] = { 0 };
	snprintf(buffer, sizeof(buffer), "%s%s", getenv("HOME"), "/Documents/");
	return buffer;
#elif PLATFORM_SWITCH
	char buffer[256] = { 0 };
	snprintf(buffer, sizeof(buffer), "%s", "rom:/UEDemo1/Saved/");
	return buffer;
#elif PLATFORM_PS4
	FString path = L"/data/";
	return TCHAR_TO_UTF8(*path);
#elif PLATFORM_XBOXONE
	FString path = L"/data/";
	return TCHAR_TO_UTF8(*path);
#endif
	return TCHAR_TO_UTF8(*FPaths::ProjectSavedDir());
}

void UBaseVoiceControlSystem::OnEndpointsUpdateInfo(int32 eventID, const char* identifier)
{
	if (m_userId != string(identifier)) {
		if (eventID == ITMG_EVENT_ID_USER_ENTER) {
			int X = 0;
			int Y = 0;
			int Z = 0;

			identifierList.insert(make_pair(string(identifier), FVector(X, Y, Z)));
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ATextRenderActor* actor1 = m_pActor->GetWorld()->SpawnActor<ATextRenderActor>(FVector(X * scaleSize, Y * scaleSize, Z * scaleSize + 100), FRotator(0, 180, 0), param);
			actor1->GetTextRender()->SetText(FText::FromString(identifier));
			actor1->GetTextRender()->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
			actor1->GetTextRender()->SetTextRenderColor(FColor(0, 0, 255, 255));

			UClass* cls = LoadClass<UObject>(NULL, TEXT("/Game/AnimStarterPack/Ue4ASP_Character.Ue4ASP_Character_C"));
			if (cls == NULL) {
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, "cls == NULL");
			}
			FVector loc(X * scaleSize, Y * scaleSize, Z * scaleSize);
			FRotator rot(0, 180, 0);
			AActor* actor2 = m_pActor->GetWorld()->SpawnActor(cls, &loc, &rot, param);
			actorList.insert(make_pair(string(identifier), make_pair(actor1, actor2)));

			FString msg = FString::Printf(TEXT("Enter id = %ls %d,%d,%d"), UTF8_TO_TCHAR(identifier), X, Y, Z);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);
		}
		else if (eventID == ITMG_EVENT_ID_USER_EXIT) {
			std::map<std::string, pair<AActor*, AActor*>>::iterator iter = actorList.find(string(identifier));
			if (iter != actorList.end()) {
				if (iter->second.first != NULL) {
					m_pActor->GetWorld()->DestroyActor(iter->second.first);
				}

				if (iter->second.second != NULL) {
					m_pActor->GetWorld()->DestroyActor(iter->second.second);
				}
			}
			identifierList.erase(string(identifier));
			actorList.erase(string(identifier));
		}
	}

	FString msg = FString::Printf(TEXT("OnEndpointsUpdateInfo event = %d, id = %ls"), eventID, UTF8_TO_TCHAR(identifier));
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);
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
		onEnterRoomCompleted(result, error_info);
	}
	else if (eventType == ITMG_MAIN_EVENT_TYPE_CHANGE_ROOM_TYPE) {
		int32 nResult = JsonObject->GetIntegerField(TEXT("result"));
		FString error_info = JsonObject->GetStringField(TEXT("error_info"));
		int nSubEventType = JsonObject->GetIntegerField(TEXT("sub_event_type"));
		int nNewType = JsonObject->GetIntegerField(TEXT("new_room_type"));

		FString msg("CHANGE_ROOM_TYPE");
		switch (nSubEventType) {
		case ITMG_ROOM_CHANGE_EVENT_ENTERROOM:
			msg = FString::Printf(TEXT("onRoomTypeChanged ITMG_ROOM_CHANGE_EVENT_ENTERROOM nNewType=%d"), nNewType);
			break;
		case ITMG_ROOM_CHANGE_EVENT_COMPLETE:
			msg = FString::Printf(TEXT("onRoomTypeChanged ITMG_ROOM_CHANGE_EVENT_COMPLETE nNewType=%d"), nNewType);
			break;
		}
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, *msg);

	}
	else if (eventType == ITMG_MAIN_EVENT_TYPE_EXIT_ROOM) {
		onExitRoomCompleted(0, "");
	}
	else if (eventType == ITMG_MAIN_EVENT_TYPE_ROOM_DISCONNECT) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString error_info = JsonObject->GetStringField(TEXT("error_info"));
		onExitRoomCompleted(result, error_info);
	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_USER_UPDATE) {
		int32 eventId = JsonObject->GetIntegerField(TEXT("event_id"));
		TArray<TSharedPtr<FJsonValue>> UserList = JsonObject->GetArrayField(TEXT("user_list"));
		for (int i = 0; i < UserList.Num(); i++) {
			FString identifier = UserList.operator[](i)->AsString();
			OnEndpointsUpdateInfo(eventId, TCHAR_TO_UTF8(identifier.operator*()));
		}
	}
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_RECORD_COMPLETE) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString filepath = JsonObject->GetStringField(TEXT("file_path"));

		std::string path = TCHAR_TO_UTF8(filepath.operator*());
		int duration = 0;
		int filesize = 0;
		if (result == 0) {
			duration = ITMGContextGetInstance()->GetPTT()->GetVoiceFileDuration(path.c_str());
			filesize = ITMGContextGetInstance()->GetPTT()->GetFileSize(path.c_str());
		}

		onPttRecordFileCompleted(result, filepath, duration, filesize);

	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_UPLOAD_COMPLETE) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString filepath = JsonObject->GetStringField(TEXT("file_path"));
		FString fileid = JsonObject->GetStringField(TEXT("file_id"));
		onPttUploadFileCompleted(result, filepath, fileid);
	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_DOWNLOAD_COMPLETE) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString filepath = JsonObject->GetStringField(TEXT("file_path"));
		FString fileid = JsonObject->GetStringField(TEXT("file_id"));
		onPttDownloadFileCompleted(result, filepath, fileid);
	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_PLAY_COMPLETE) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString filepath = JsonObject->GetStringField(TEXT("file_path"));
		onPttPlayFileCompleted(result, filepath);
	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_SPEECH2TEXT_COMPLETE) {
		int32 result = JsonObject->GetIntegerField(TEXT("result"));
		FString text = JsonObject->GetStringField(TEXT("text"));
		FString fileid = JsonObject->GetStringField(TEXT("file_id"));
		onPttSpeech2TextCompleted(result, fileid, text);

	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_STREAMINGRECOGNITION_COMPLETE)
	{
		int32 nResult = JsonObject->GetIntegerField(TEXT("result"));
		FString text = JsonObject->GetStringField(TEXT("text"));
		FString fileid = JsonObject->GetStringField(TEXT("file_id"));
		FString file_path = JsonObject->GetStringField(TEXT("file_path"));
		onPttStreamRecognitionCompleted(nResult, file_path, fileid, text);
	}
	else if (eventType == ITMG_MAIN_EVNET_TYPE_PTT_STREAMINGRECOGNITION_IS_RUNNING)
	{
		int32 nResult = JsonObject->GetIntegerField(TEXT("result"));
		FString text = JsonObject->GetStringField(TEXT("text"));
		FString fileid = TEXT("STREAMINGRECOGNITION_IS_RUNNING");
		FString file_path = JsonObject->GetStringField(TEXT("file_path"));
		onPttStreamRecognitionisRunning(nResult, file_path, fileid, text);
	}


#endif
}

void UBaseVoiceControlSystem::onExitRoomCompleted(int32 result, FString errInfo)
{
	for (std::map<std::string, pair<AActor*, AActor*>>::iterator iter = actorList.begin(); iter != actorList.end(); iter++) {
		if (iter->second.first != NULL) {
			m_pActor->GetWorld()->DestroyActor(iter->second.first);
		}

		if (iter->second.second != NULL) {
			m_pActor->GetWorld()->DestroyActor(iter->second.second);
		}
	}
	identifierList.clear();
	actorList.clear();

	FString msg = FString::Printf(TEXT("OnEvent EXIT_ROOM reason= %d, info = %ls"), result, *errInfo);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, *msg);
}

void UBaseVoiceControlSystem::OnClickChangeDemo()
{
	time_t now = time(NULL);
	if (m_ClickCount == 0)
	{
		m_FirstClickTime = now;
	}
	m_ClickCount++;

	if (m_ClickCount == 5)
	{
		m_ClickCount = 0;
		if (now - m_FirstClickTime < 3)
		{
			m_pActor->onChangeDemo();
		}
	}
}


//int UBaseVoiceControlSystem::InitGME(std::string sdkAppId, std::string sdkAppKey, std::string OpenId)
//{
//	//初始化sdk   by Mr-cao 20201126
//	int nAppId = atoi(sdkAppId.c_str());
//	int ret = ITMGContextGetInstance()->Init(sdkAppId.c_str(), OpenId.c_str());
//	ITMGContextGetInstance()->SetTMGDelegate(this);
//
//	//检查麦克风许可
//	int RetCode = (int)ITMGContextGetInstance()->CheckMicPermission();
//	FString mag = FString::Printf(TEXT("check Permission retcode = %d"), RetCode);
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *mag);
//
//	char strSig[128] = { 0 };
//	unsigned int nLength = 128;
//	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppId, "0", OpenId.c_str(), sdkAppKey.c_str(), (unsigned char*)strSig, nLength);
//	ITMGContextGetInstance()->GetPTT()->ApplyPTTAuthbuffer(strSig, nLength);
//	ITMGContextGetInstance()->SetAdvanceParams("ForceHighQuanlityState", "0");
//
//	m_appId = sdkAppId;
//	m_appKey = sdkAppKey;
//	m_userId = OpenId;
//
//	return ret;
//}
//
//void UBaseVoiceControlSystem::EnterRoom(std::string roomId, ITMG_ROOM_TYPE roomType)
//{
//	int nAppId = atoi(m_appId.c_str());
//
//	char strSig[128] = { 0 };
//	unsigned int nLength = 128;
//	nLength = QAVSDK_AuthBuffer_GenAuthBuffer(nAppId, roomId.c_str(), m_userId.c_str(), m_appKey.c_str(), (unsigned char*)strSig, nLength);
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnEnterRoom"));
//	ITMGContextGetInstance()->EnterRoom(roomId.c_str(), roomType, strSig, nLength);
//}
//
//void UBaseVoiceControlSystem::OnEvent(ITMG_MAIN_EVENT_TYPE eventType, const char* data)
//{
	//FString jsonData = FString(UTF8_TO_TCHAR(data));
	//TSharedPtr<FJsonObject> JsonObject;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FString(UTF8_TO_TCHAR(data)));
	//FJsonSerializer::Deserialize(Reader, JsonObject);


	//if (eventType == ITMG_MAIN_EVENT_TYPE_ENTER_ROOM) {
	//	int32 result = JsonObject->GetIntegerField(TEXT("result"));
	//	FString error_info = JsonObject->GetStringField(TEXT("error_info"));
	//	if (result == 0) {
	//		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, TEXT("Enter room success."));
	//	}
	//	else {
	//		FString msg = FString::Printf(TEXT("Enter room failed. result=%d, info = %ls"), result, *error_info);
	//		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, *msg);
	//	}
	//	//onEnterRoomCompleted(result, error_info);
	//}
//}
