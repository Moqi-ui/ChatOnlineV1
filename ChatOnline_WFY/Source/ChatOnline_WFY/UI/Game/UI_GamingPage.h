// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_CoreBase.h"
#include "UI_GamingPage.generated.h"

/**
 * 
 */
class UTexture2D;

class UBaseVoiceControlSystem;
UCLASS()
class CHATONLINE_WFY_API UUI_GamingPage : public UUI_CoreBase
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UButton* GamingMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* Mic;

	UPROPERTY(meta = (BindWidget))
		class UButton* Speaker;

	UPROPERTY(meta = (BindWidget))
		class UButton* EarToReturnButton;

	UPROPERTY(meta = (BindWidget))
		class UImage* Mic_Image;

	UPROPERTY(meta = (BindWidget))
		class UImage* Speaker_Image;

	UPROPERTY(meta = (BindWidget))
		class UImage* EarToReturn_Image;

	UPROPERTY(meta = (BindWidget))
		class UButton* RoomPageButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* VoicePageButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* SetingPageButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitRoom;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitGame;

	UPROPERTY(meta = (BindWidget))
		class UButton* ReturnGmaing;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextRoomName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextRoomID;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextPlyaerNumber;

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* GameMenuPage;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* GameSwitchPage;

public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

private:

	UFUNCTION()
	void OnClickMenuButton();

	UFUNCTION()
	void OnClickMicButton();

	UFUNCTION()
	void OnClickSpeakerButton();

	UFUNCTION()
	void OnClickEarToReturnButton();

	UFUNCTION()
	void SwitchRoomPage();

	UFUNCTION()
	void SwitchVoicePage();

	UFUNCTION()
	void SwitchSettingPage();

	UFUNCTION()
	void RequestExitRoom();

	UFUNCTION()
	void RequestExitGame();

	UFUNCTION()
	void ReturnGaming();

private:

	void UpdateRoomInfo(FString CurrentPlayerNumber);

private:

	UTexture2D* SpeackCheck;
	UTexture2D* SpeackUncheck;
	UTexture2D* MicCheck;
	UTexture2D* MicUncheck;

	UPROPERTY()
	UBaseVoiceControlSystem* BaseVoiceControl;
	//UTexture2D* SpeackCheck;

	FString UserID;

	bool MicState = false;
	bool SpeakerState = false;
	bool EarState = false;

	bool bIsExitGame = false;
};
