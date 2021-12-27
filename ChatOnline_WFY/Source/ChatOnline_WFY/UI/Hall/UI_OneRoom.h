// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @author			Imrcao						(曹洛)
* @date				2021，11，11, 11:32: 00		(2018年09月28日10:30 : 00)
* @brief			Register UI					(注册UI界面)
* @see
* @See				http://www.imrcao.com
* @note
**********************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "UI_OneRoom.generated.h"

//class UUI_HallMain;

DECLARE_DELEGATE_OneParam(DE_JoinRoom, FString)

UCLASS()
class UUI_OneRoom : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinRoomButto;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* RoomInfo;


public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	void SetRoomInfo(FString ServerRoomInfo);

	DE_JoinRoom JoinRoom;

private:

	UFUNCTION()
	void OnClickJoinRoomButton();

private:

	FString RoomPort;

	FString RoomName;

};

