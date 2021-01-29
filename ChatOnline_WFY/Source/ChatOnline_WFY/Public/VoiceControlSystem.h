// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @copyright 2020-2021,com.imrcao，All right reserved
*
* @author imrcao
*
* @date 2021年01月27日16:25:00
*
* @brief 语音控制相关函数
*
* @See 
*
**********************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BaseVoiceControlSystem.h"
#include "UserWidget.h"
#include "Sound/SoundWave.h"
#include "VoiceControlSystem.generated.h"


UCLASS(Blueprintable, BlueprintType)
class CHATONLINE_WFY_API UVoiceControlSystem : public UBaseVoiceControlSystem//, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UVoiceControlSystem() {}
	virtual ~UVoiceControlSystem() {}
	virtual bool Create(ALevelScriptActorRoom* pActor);
	virtual void Destory();
	virtual void Show(bool bShow);

	UFUNCTION()
		void onChangeDemo();

	UFUNCTION(BlueprintCallable, Category = "GME")
		void onInitGME();

	UFUNCTION(BlueprintCallable, Category = "GME")
		void onUnInitGME();

	UFUNCTION(BlueprintCallable, Category = "GME")
		void onEnterRoom();

	UFUNCTION(BlueprintCallable, Category = "GME")
		void onExitRoom();

	UFUNCTION(BlueprintCallable, Category = "GME")
		void onCheckMic(bool isChecked);

	UFUNCTION(BlueprintCallable, Category = "GME")
		void onCheckSpeaker(bool isChecked);

	UFUNCTION()
		void onCheckSpatializer(bool isChecked);

	UFUNCTION()
		void onCheckTips(bool isChecked);

	UFUNCTION()
		void onCheckEnable3DInTeam(bool isChecked);

	UFUNCTION()
		void onCheckVoiceChange(bool isChecked);

	UFUNCTION()
		void onEditTeamIDChange(const FText& Text);

	UFUNCTION()
		void onCheckRangeAudioModeChange(bool isChecked);

	UFUNCTION()
		void onChangeRoomType();

	UFUNCTION()
		void onPttRecordPress();

	UFUNCTION()
		void onPttRecordRelease();

	UFUNCTION()
		void onPttRecordHover();

	UFUNCTION()
		void onPttRecordUnhover();

	UFUNCTION()
		void onPttPlay();

	UFUNCTION()
		void onPttUpload();

	UFUNCTION()
		void onPttDownload();

	UFUNCTION()
		void onPtt2Text();

	UFUNCTION()
		void onStreamRecordRelease();

	UFUNCTION()
		void onStreamRecordPress();

	UFUNCTION()
		void onBGMPress();

	UFUNCTION()
		void onPause();

	UFUNCTION()
		void onResume();

protected:
	virtual void SetPositionInfo(FString);
	virtual void SetTips(std::string tips);
	virtual int GetRange();
	virtual void onEnterRoomCompleted(int32 result, FString errInfo);
	virtual void onPttRecordFileCompleted(int32 result, FString filePath, int duration, int filesize);
	virtual void onPttPlayFileCompleted(int32 result, FString filePath);
	virtual void onPttUploadFileCompleted(int32 result, FString filePath, FString fileID);
	virtual void onPttDownloadFileCompleted(int32 result, FString filePath, FString fileID);
	virtual void onPttSpeech2TextCompleted(int32 result, FString fileID, FString text);
	void onPttStreamRecognitionCompleted(int32 result, FString filePath, FString fileID, FString text);

	void onPttStreamRecognitionisRunning(int32 result, FString filePath, FString fileID, FString text);

private:
	//UUEDemoUserWidget* m_Widget;
	UUserWidget* m_Widget;
	bool m_isEnable3DInTeam;
	void pttPrintBusyInfo();
	PttState m_pttState;
	std::string m_fileUrl;
	std::string m_filePath;
	bool m_isRecordHover;
	USoundWave* mySound;
	bool m_isPlaysound = false;
	
};
