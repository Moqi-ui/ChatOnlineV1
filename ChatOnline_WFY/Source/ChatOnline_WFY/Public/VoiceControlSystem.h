// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @copyright 2020-2021,com.imrcao��All right reserved
*
* @author imrcao
*
* @date 2021��01��27��16:25:00
*
* @brief ����������غ���
*
* @See 
*
**********************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BaseVoiceControlSystem.h"
#include "VoiceControlSystem.generated.h"


UCLASS(Blueprintable, BlueprintType)
class CHATONLINE_WFY_API UVoiceControlSystem : public UBaseVoiceControlSystem, public FTickableGameObject
{
	GENERATED_BODY()

public:

	UVoiceControlSystem();

	~UVoiceControlSystem();

	//��дFTickableGameObject�Ĵ��麯��
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;


public:

	//������صĿ��ƺ���������ͼ����
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

	UFUNCTION(BlueprintCallable, Category = "Debug")
		void Debug(FString msg);
	
};
