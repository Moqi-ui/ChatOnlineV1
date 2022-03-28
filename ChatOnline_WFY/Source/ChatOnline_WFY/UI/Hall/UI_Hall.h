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
#include "../Core/UI_CoreBase.h"
#include "UI_Hall.generated.h"

//class UUI_HallMain;

UCLASS()
class UUI_Hall : public UUI_CoreBase
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UButton* MenuButton;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* MenuPage;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* LoadPage;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* RoomPage;

	UPROPERTY(meta = (BindWidget))
		class UButton* SerachRoom;

	UPROPERTY(meta = (BindWidget))
		class UButton* SelectCharacter;

	UPROPERTY(meta = (BindWidget))
		class UButton* Setting;

	UPROPERTY(meta = (BindWidget))
		class UButton* CreateRoomButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* LogOut;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitGame;

	/*UPROPERTY(meta = (BindWidget))
		class UButton* JoinRoomButton;*/

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	/*UPROPERTY(meta = (BindWidget))
		class UCircularThrobber* SerachCircularThrobber;*/

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* ScrollRoomList;

	UPROPERTY(meta = (BindWidget))
		class UButton* FindRoomButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ServerMap1Buuton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ServerMap2Buuton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ServerMap3Buuton;



	//UPROPERTY(meta = (BindWidget))
		//class UTextBlock* UserInputRoomName;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//提示错误信息
	void LoginMsg(FString Mes);

	void LoginCallback();

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	UFUNCTION(BluePrintCallable)
		void SetInputRoomName(FText tt);

private:

	UFUNCTION()
	void OpenMenuPage();

	UFUNCTION()
	void CloseMenuPage();

	UFUNCTION()
	void SwitchCreateRoomPage();

	UFUNCTION()
	void SwiichSerachRoomPage();

	UFUNCTION()
	void TryCreateRoom();

	UFUNCTION()
	void SerachCurrentRoom();

	UFUNCTION()
	void JoinCurrentSelectedRoom(FString HandleRoomInfo);

	UFUNCTION()
		void OnClickServerMapButton1();

	UFUNCTION()
		void OnClickServerMapButton2();

	UFUNCTION()
		void OnClickServerMapButton3();

	UFUNCTION()
		void SwitchCharacterPage();

	UFUNCTION()
		void SwitchSettingPage();

	UFUNCTION()
		void TryLogOut();

	UFUNCTION()
		void TryExitGame();

private:

	void CreateRoomWidget(FString ServerNameInfo);

	void AnalysisString(FString Str);

	void ResetButtonColor();

private:

	TArray<FString> ServerRooms;

	FText UserRoomName;

	FString ServerMapName = "ZWB";

};

