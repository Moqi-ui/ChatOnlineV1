// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceControlSystem.h"
#include "LevelScriptActorRoom.h"
#include "UserConfig.h"
#include <math.h>
#include <time.h>
#include <vector>
#include <wchar.h>
#include <AudioDeviceManager.h>
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

using namespace std;

#define DEMO_VERSION "Unreal Demo Local"

bool UVoiceControlSystem::Create(ALevelScriptActorRoom* pActor) {
	if (m_isCreated) {
		return true;
	}

	if (!pActor) {
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("UVoiceControlSystem::Create|pActor == NULL."));
		return false;
	}
	m_pActor = pActor;
	m_pttState = PttState_None;
	m_isRecordHover = false;
	m_isEnable3DInTeam = false;
	m_isCreated = true;

	//TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(NULL, TEXT("Blueprint'/Game/UEDemoWidgetBlueprint.UEDemoWidgetBlueprint_C'"));
	//m_Widget = CreateWidget<UUEDemoUserWidget>(m_pActor->GetWorld(), WidgetClass);

	//m_Widget->AddToViewport();
	//m_Widget->SetVisibility(ESlateVisibility::Hidden);

	return true;

}
void UVoiceControlSystem::Destory() {
	if (!m_isCreated) {
		return;
	}

	m_isCreated = false;
	//m_Widget->RemoveFromViewport();
	m_pActor = NULL;
}


void UVoiceControlSystem::Show(bool bShow) {
	if (!m_isCreated) {
		return;
	}

	//m_Widget->SetVisibility(bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	if (!bShow)
	{
		ITMGContextGetInstance()->Uninit();
	}
}

void UVoiceControlSystem::onChangeDemo() {
	OnClickChangeDemo();
}
void UVoiceControlSystem::onInitGME() {

	/*std::string appid = TCHAR_TO_UTF8(m_Widget->editAppID->GetText().ToString().operator*());
	std::string appkey = TCHAR_TO_UTF8(m_Widget->editAppKey->GetText().ToString().operator*());
	std::string userId = TCHAR_TO_UTF8(m_Widget->editUserID->GetText().ToString().operator*());*/


	FString strAppId = "1400452190";
	FString strKey = "U8fTpuA3H0tl4PyI";

	srand(time(NULL));
	int uid = rand() % 10000 + 50000;
	FString strUserId = FString::FromInt(uid);
	//FMath::RandRange()

	std::string appid = TCHAR_TO_UTF8(*strAppId);
	std::string appkey = TCHAR_TO_UTF8(*strKey);
	std::string userId = TCHAR_TO_UTF8(*strUserId);

	UserConfig::SetAppID(appid);
	UserConfig::SetAppKey(appkey);

	//ITMGContextGetInstance()->SetTestEnv(m_Widget->checkBoxTestEnv->IsChecked());	// warning : never call this API for any reason, it's only for internal use
	//ITMGContextGetInstance()->SetAppVersion(DEMO_VERSION);		// Just For Test
	int ret = InitGME(appid, appkey, userId);
	ITMGContextGetInstance()->SetAdvanceParams("SetStreamingRecTimeOut", "5");
	FString msg = FString::Printf(TEXT("onLogin ret=%d"), ret);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, msg);
}

void UVoiceControlSystem::onUnInitGME() {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onLogout"));
	ITMGContextGetInstance()->Uninit();
}

void UVoiceControlSystem::onEnterRoom() {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onEnterRoom"));
	FString RoomIDStr = "202101";
	std::string roomID = TCHAR_TO_UTF8(*RoomIDStr);
	//std::string roomType = TCHAR_TO_UTF8(m_Widget->editRoomType->GetText().ToString().operator*());
	//int nRoomType = atoi(roomType.c_str());

	EnterRoom(roomID, (ITMG_ROOM_TYPE)0);
}

void UVoiceControlSystem::onExitRoom() {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onExitRoom"));
	ITMGContextGetInstance()->ExitRoom();
}

void UVoiceControlSystem::onCheckMic(bool isChecked) {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckMic"));
	ITMGContextGetInstance()->GetAudioCtrl()->EnableMic(isChecked);
}

void UVoiceControlSystem::onCheckSpeaker(bool isChecked) {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckSpeaker"));
	ITMGContextGetInstance()->GetAudioCtrl()->EnableSpeaker(isChecked);
}

void UVoiceControlSystem::SetPositionInfo(FString positionInfo) {
	//m_Widget->textCamera->SetText(FText::FromString(*positionInfo));
}
int UVoiceControlSystem::GetRange() {

	int nRange = 0;
	if (m_Widget != nullptr)
	{
		//nRange = atoi(TCHAR_TO_UTF8(m_Widget->editRange->GetText().ToString().operator*()));
	}
	return nRange;
}

void UVoiceControlSystem::SetTips(std::string tips) {
	if (m_Widget != nullptr) {
		FString tempTips = FString(UTF8_TO_TCHAR(tips.c_str()));
		//m_Widget->textTips->SetText(FText::FromString(tempTips));
	}
}

void UVoiceControlSystem::pttPrintBusyInfo() {
	//FString temp = m_Widget->textPttInfo->GetText().ToString();
	if (m_pttState == PttState_Recording) {
		//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nwarning: recording!!!"));
	}
	else if (m_pttState == PttState_Playing) {
		//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nwarning: playing!!!"));
	}
	else if (m_pttState == PttState_Uploading) {
		//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nwarning: uploading!!!"));
	}
	else if (m_pttState == PttState_Downloading) {
		//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nwarning: downloading!!!"));
	}
	else if (m_pttState == PttState_ToTexting) {
		//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nwarning: totexting!!!"));
	}
}

void UVoiceControlSystem::onStreamRecordPress()
{
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_None) {
		m_pttState = PttState_Recording;
		m_isRecordHover = true;
		//m_Widget->textPttInfo->SetText(FText::FromString("Stream: recording..."));
		m_filePath = "";

		char buffer[256] = { 0 };
		snprintf(buffer, sizeof(buffer), "%sunreal_ptt_local.file", getFilePath().c_str());
		ITMGContextGetInstance()->GetPTT()->StartRecordingWithStreamingRecognition(buffer, "cmn-Hans-CN");
	}
	else {
		pttPrintBusyInfo();
	}
#endif
}
void UVoiceControlSystem::onBGMPress()
{
	mySound = LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/bgm.bgm'"));
	if (m_isPlaysound) {
		FAudioDeviceManager* Manager = GEngine->GetAudioDeviceManager();
		if (Manager)
		{
			Manager->StopSoundsUsingResource(mySound);
			m_isPlaysound = false;
		}

	}
	else {
		if (mySound)
		{
			mySound->bLooping = true;
			UGameplayStatics::PlaySound2D(m_pActor->GetWorld(), mySound);
			m_isPlaysound = true;
		}
	}

}
void UVoiceControlSystem::onStreamRecordRelease() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_Recording) {
		if (m_isRecordHover) {
			//m_Widget->textPttInfo->SetText(FText::FromString("Stream: release..."));
			ITMGContextGetInstance()->GetPTT()->StopRecording();
		}
		else {
			ITMGContextGetInstance()->GetPTT()->CancelRecording();
			//m_Widget->textPttInfo->SetText(FText::FromString("info: recording canceled."));
			m_pttState = PttState_None;
		}
	}
#endif
}


void UVoiceControlSystem::onPttRecordPress() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_None) {
		m_pttState = PttState_Recording;
		m_isRecordHover = true;
		//m_Widget->textPttInfo->SetText(FText::FromString("info: recording..."));
		//m_Widget->textRecord->SetText(FText::FromString("Recording"));
		m_filePath = "";
		char buffer[256] = { 0 };
		snprintf(buffer, sizeof(buffer), "%sunreal_ptt_local.file", getFilePath().c_str());
		ITMGContextGetInstance()->GetPTT()->StartRecording(buffer);
	}
	else {
		pttPrintBusyInfo();
	}
#endif
}
void UVoiceControlSystem::onPttRecordRelease() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_Recording) {
		if (m_isRecordHover) {
			ITMGContextGetInstance()->GetPTT()->StopRecording();
		}
		else {
			ITMGContextGetInstance()->GetPTT()->CancelRecording();
			//m_Widget->textPttInfo->SetText(FText::FromString("info: recording canceled."));
		//	m_Widget->textRecord->SetText(FText::FromString("Record"));
			m_pttState = PttState_None;
		}
	}
#endif
}
void UVoiceControlSystem::onPttRecordHover() {
	m_isRecordHover = true;
}
void UVoiceControlSystem::onPttRecordUnhover() {
	m_isRecordHover = false;
}




void UVoiceControlSystem::onPause() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	ITMGContextGetInstance()->GetPTT()->PauseRecording();
#endif
}
void UVoiceControlSystem::onResume() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	ITMGContextGetInstance()->GetPTT()->ResumeRecording();
#endif
}



void UVoiceControlSystem::onPttPlay() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_None) {
		if (m_filePath == "") {
			//FString temp = m_Widget->textPttInfo->GetText().ToString();
			//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nerror: local path is empty!!!"));
			return;
		}
		m_pttState = PttState_Playing;
		//m_Widget->textPttInfo->SetText(FText::FromString("info: playing..."));
		//m_Widget->textPlay->SetText(FText::FromString("Stop"));
		ITMGContextGetInstance()->GetPTT()->PlayRecordedFile(m_filePath.c_str());
	}
	else if (m_pttState == PttState_Playing) {
		ITMGContextGetInstance()->GetPTT()->StopPlayFile();
	}
	else {
		pttPrintBusyInfo();
	}
#endif
}
void UVoiceControlSystem::onPttUpload() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_None) {
		if (m_filePath == "") {
			//FString temp = m_Widget->textPttInfo->GetText().ToString();
			//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nerror: local path is empty!!!"));
			return;
		}
		m_pttState = PttState_Uploading;
		//m_Widget->textPttInfo->SetText(FText::FromString("info: uploading..."));

		m_fileUrl = "";
		ITMGContextGetInstance()->GetPTT()->UploadRecordedFile(m_filePath.c_str());
	}
	else {
		pttPrintBusyInfo();
	}

#endif
}
void UVoiceControlSystem::onPttDownload() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC

	if (m_pttState == PttState_None) {
		if (m_fileUrl == "") {
			//FString temp = m_Widget->textPttInfo->GetText().ToString();
			//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nerror: url is empty!!!"));
			return;
		}
		m_pttState = PttState_Downloading;
		//m_Widget->textPttInfo->SetText(FText::FromString("info: downloading..."));
		m_filePath = "";
		char buffer[256] = { 0 };
		snprintf(buffer, sizeof(buffer), "%sunreal_ptt_download.file", getFilePath().c_str());
		ITMGContextGetInstance()->GetPTT()->DownloadRecordedFile(m_fileUrl.c_str(), buffer);
	}
	else {
		pttPrintBusyInfo();
	}

#endif
}
void UVoiceControlSystem::onPtt2Text() {
#if PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_WINDOWS || PLATFORM_MAC
	if (m_pttState == PttState_None) {
		if (m_fileUrl == "") {
			//FString temp = m_Widget->textPttInfo->GetText().ToString();
			//m_Widget->textPttInfo->SetText(FText::FromString(temp + "\nerror: url is empty!!!"));
			return;
		}
		m_pttState = PttState_ToTexting;
		//m_Widget->textPttInfo->SetText(FText::FromString("info: totexting..."));

		ITMGContextGetInstance()->GetPTT()->SpeechToText(m_fileUrl.c_str());
	}
	else {
		pttPrintBusyInfo();
	}

#endif
}
void UVoiceControlSystem::onCheckSpatializer(bool isChecked) {
	char buffer[256] = { 0 };
	//    snprintf(buffer, sizeof(buffer), "%s3d_model", getFilePath().c_str());
	snprintf(buffer, sizeof(buffer), "%sgme_2.8_3d_model.dat", getFilePath().c_str());
	int ret1 = ITMGContextGetInstance()->GetAudioCtrl()->InitSpatializer(buffer);
	int ret2 = ITMGContextGetInstance()->GetAudioCtrl()->EnableSpatializer(isChecked, m_isEnable3DInTeam);
	FString msg = FString::Printf(TEXT("InitSpatializer=%d, EnableSpatializer ret=%d"), ret1, ret2);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, msg);
}

void UVoiceControlSystem::onCheckVoiceChange(bool isChecked) {
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckVoiceChange"));

	ITMGAudioEffectCtrl* pTmgCtrl = ITMGContextGetInstance()->GetAudioEffectCtrl();
	if (!pTmgCtrl) {
		return;
	}

	if (isChecked) {
		ITMGContextGetInstance()->GetAudioEffectCtrl()->SetVoiceType(ITMG_VOICE_TYPE_LOLITA);
	}
	else {
		ITMGContextGetInstance()->GetAudioEffectCtrl()->SetVoiceType(ITMG_VOICE_TYPE_ORIGINAL_SOUND);
	}
}

void UVoiceControlSystem::onEditTeamIDChange(const FText& Text)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onEditTeamIDChange"));

	std::string text = TCHAR_TO_UTF8(Text.ToString().operator*());
	int teamID = atoi(text.c_str());
	ITMGContextGetInstance()->SetRangeAudioTeamID(teamID);
}

void UVoiceControlSystem::onCheckTips(bool isChecked) {
	m_isEnableTips = isChecked;
	if (!m_isEnableTips) {
		//m_Widget->textTips->SetText(FText::FromString(""));
	}

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckTips"));
}

void UVoiceControlSystem::onCheckEnable3DInTeam(bool isChecked) {
	m_isEnable3DInTeam = isChecked;
	if (ITMGContextGetInstance()->GetAudioCtrl()->IsEnableSpatializer()) {
		ITMGContextGetInstance()->GetAudioCtrl()->EnableSpatializer(true, m_isEnable3DInTeam);
	}
}

void UVoiceControlSystem::onCheckRangeAudioModeChange(bool isChecked) {
	ITMG_RANGE_AUDIO_MODE audioMode = isChecked ? ITMG_RANGE_AUDIO_MODE_TEAM : ITMG_RANGE_AUDIO_MODE_WORLD;
	ITMGContextGetInstance()->SetRangeAudioMode(audioMode);

	FString msg = FString::Printf(TEXT("onChangeMode audioMode=%d"), (int)audioMode);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);
}

void UVoiceControlSystem::onChangeRoomType() {
	//std::string roomType = TCHAR_TO_UTF8(m_Widget->editRoomType->GetText().ToString().operator*());
	//int nRoomType = atoi(roomType.c_str());
	//ITMGContextGetInstance()->GetRoom()->ChangeRoomType((ITMG_ROOM_TYPE)nRoomType);

	//FString msg = FString::Printf(TEXT("onChangeRoomType nRoomType=%d"), nRoomType);
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, *msg);
}

void UVoiceControlSystem::onEnterRoomCompleted(int32 result, FString errInfo) {
	if (result == 0) {
		//m_Widget->checkBoxMic->SetIsChecked(false);
	//	m_Widget->checkBoxSpeaker->SetIsChecked(false);
		//m_Widget->checkBoxSpatializer->SetIsChecked(false);
	//	m_Widget->checkBoxVoiceChange->SetIsChecked(false);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 20.0f, FColor::Yellow, TEXT("OnEvent ENTER_ROOM succ"));
	}
}

void UVoiceControlSystem::onPttRecordFileCompleted(int32 result, FString filePath, int duration, int filesize) {
	m_filePath = TCHAR_TO_UTF8(filePath.operator*());
	FString msg = FString::Printf(TEXT("info: recording completed.\nreslut=%d\nfilepath=%ls\nduarion=%.2f\nfilesize=%.2fKB"), result, filePath.operator*(), duration / 1000.0f, filesize / 1024.0f);

	//m_Widget->textPttInfo->SetText(FText::FromString(*msg));
	//m_Widget->textRecord->SetText(FText::FromString("Record"));
	m_pttState = PttState_None;
}
void UVoiceControlSystem::onPttPlayFileCompleted(int32 result, FString filePath) {
	FString msg = FString::Printf(TEXT("info: playing completed.\nreslut=%d\nfilepath=%ls"), result, filePath.operator*());
	//m_Widget->textPttInfo->SetText(FText::FromString(*msg));
	//m_Widget->textPlay->SetText(FText::FromString("Play"));
	m_pttState = PttState_None;
}
void UVoiceControlSystem::onPttUploadFileCompleted(int32 result, FString filePath, FString fileID) {
	m_fileUrl = TCHAR_TO_UTF8(fileID.operator*());
	FString msg = FString::Printf(TEXT("info: uploading completed.\nreslut=%d\nfilepath=%ls\nfileid=%ls"), result, filePath.operator*(), fileID.operator*());
	//m_Widget->textPttInfo->SetText(FText::FromString(*msg));
	m_pttState = PttState_None;
}
void UVoiceControlSystem::onPttDownloadFileCompleted(int32 result, FString filePath, FString fileID) {
	m_filePath = TCHAR_TO_UTF8(filePath.operator*());
	FString msg = FString::Printf(TEXT("info: downloading completed.\nreslut=%d\nfilepath=%ls\nfileid=%ls"), result, filePath.operator*(), fileID.operator*());
	//m_Widget->textPttInfo->SetText(FText::FromString(*msg));
	m_pttState = PttState_None;
}
void UVoiceControlSystem::onPttSpeech2TextCompleted(int32 result, FString fileID, FString text) {
	FString debugText = FString::Printf(TEXT("info: totexting completed.\nreslut=%d\ntext=%ls"), result, *text);
	//m_Widget->textPttInfo->SetText(FText::FromString(debugText));
	m_pttState = PttState_None;
}

void UVoiceControlSystem::onPttStreamRecognitionCompleted(int32 result, FString filePath, FString fileID, FString text) {

	m_filePath = TCHAR_TO_UTF8(filePath.operator*());
	m_fileUrl = TCHAR_TO_UTF8(fileID.operator*());

	FString debugText = FString::Printf(TEXT("info: stream completed.\nreslut=%d\ntext=%ls\nfilePath=%ls\nfileID=%ls"), result, *text, *filePath, *fileID);
	//m_Widget->textPttInfo->SetText(FText::FromString(debugText));


	m_pttState = PttState_None;
}

void UVoiceControlSystem::onPttStreamRecognitionisRunning(int32 result, FString filePath, FString fileID, FString text) {

	m_filePath = TCHAR_TO_UTF8(filePath.operator*());
	m_fileUrl = TCHAR_TO_UTF8(fileID.operator*());

	FString debugText = FString::Printf(TEXT("info: stream runnig.\nreslut=%d\ntext=%ls\nfilePath=%ls\nfileID=%ls"), result, *text, *filePath, *fileID);
//	m_Widget->textPttInfo->SetText(FText::FromString(debugText));


	// m_pttState = PttState_None;
}


//void UVoiceControlSystem::Tick(float DeltaTime)
//{
//	ITMGContextGetInstance()->Poll();
//}
//
//bool UVoiceControlSystem::IsTickable() const
//{
//
//	return true;
//}
//
//TStatId UVoiceControlSystem::GetStatId() const
//{
//	return Super::GetStatID();
//}

//void UVoiceControlSystem::OnInitGME()
//{
//	FString strAppId = "1400452190";
//	FString strKey = "U8fTpuA3H0tl4PyI";
//
//	srand(time(NULL));
//	int uid = rand() % 10000 + 50000;
//	FString strUserId = FString::FromInt(uid);
//	//FMath::RandRange()
//
//	std::string appid = TCHAR_TO_UTF8(*strAppId);
//	std::string appkey = TCHAR_TO_UTF8(*strKey);
//	std::string userId = TCHAR_TO_UTF8(*strUserId);
//
//	int ret = InitGME(appid, appkey, userId);
//
//	ITMGContextGetInstance()->SetAdvanceParams("SetStreamingRecTimeOut", "5");
//	FString msg = FString::Printf(TEXT("onLogin ret=%d"), ret);
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, msg);
//
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.0f, FColor::Green, "strAppId:" + strAppId);
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.0f, FColor::Green, "strKey:" + strKey);
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.0f, FColor::Green, "strUserId:" + strUserId);
//}
//
//void UVoiceControlSystem::OnEnterRoom(FString roomId)
//{
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onEnterRoom"));
//	std::string strRoomID = TCHAR_TO_UTF8(*roomId);
//
//	EnterRoom(strRoomID, (ITMG_ROOM_TYPE)0);
//}
//
//void UVoiceControlSystem::OnExitRoom()
//{
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onExitRoom"));
//	ITMGContextGetInstance()->ExitRoom();
//}
//
//void UVoiceControlSystem::onCheckMic(bool isChecked)
//{
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckMic"));
//	ITMGContextGetInstance()->GetAudioCtrl()->EnableMic(isChecked);
//}
//
//void UVoiceControlSystem::onCheckSpeaker(bool isChecked)
//{
//	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("onCheckSpeaker"));
//	ITMGContextGetInstance()->GetAudioCtrl()->EnableSpeaker(isChecked);
//}
//
//void UVoiceControlSystem::Debug(FString msg)
//{
//
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, *msg);
//}