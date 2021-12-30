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
};
