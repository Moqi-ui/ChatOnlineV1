// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_CoreBase.h"
#include "UI_GamingPage.generated.h"

/**
 * 
 */
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

};
