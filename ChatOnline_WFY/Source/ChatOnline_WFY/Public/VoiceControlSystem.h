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
#include "VoiceControlSystem.generated.h"


UCLASS(Blueprintable, BlueprintType)
class CHATONLINE_WFY_API UVoiceControlSystem : public UBaseVoiceControlSystem
{
	GENERATED_BODY()

public:
	UVoiceControlSystem() {}
	virtual ~UVoiceControlSystem() {}

	UFUNCTION(BlueprintCallable, Category = "GME")
	void OnInitGME();

	UFUNCTION(BlueprintCallable, Category = "GME")
	void OnEnterRoom(FString roomId);

	UFUNCTION(BlueprintCallable, Category = "GME")
	void OnExitRoom();

	UFUNCTION(BlueprintCallable, Category = "GME")
	void onCheckMic(bool isChecked);

	UFUNCTION(BlueprintCallable, Category = "GME")
	void onCheckSpeaker(bool isChecked);

	UFUNCTION(BLueprintCallable, Category = "GME")
		void EarToReturn(bool icChecked);
	
};
