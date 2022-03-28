
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_TopTitle.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Gaming/ChatOnLine_GameInstance.h"
#include "Engine/Texture2D.h"

void UUI_TopTitle::NativeConstruct()
{
	Super::NativeConstruct();

	Speaking = LoadObject<UTexture2D>(this, TEXT("/Game/ChatOnline/WFY_Textture/Icon/Speaker_Check"));
	NoSpeaker = LoadObject<UTexture2D>(this, TEXT("/Game/ChatOnline/WFY_Textture/Icon/Speaker_Uncheck"));

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	SetTitle(Instance->GetUserInfo().userName);
}

void UUI_TopTitle::NativeDestruct()
{
	Super::NativeDestruct();
}
void UUI_TopTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	if (Instance->GetUserSpeakerState())
	{
		SetStateImage(Speaking);
	}
	else
	{
		SetStateImage(NoSpeaker);
	}
}


void UUI_TopTitle::SetTitle(FString Titile)
{
	PlayerName->SetText(FText::FromString(Titile));
}

void UUI_TopTitle::SetStateImage(UTexture2D* Image)
{
	SpeakImage->SetBrushFromTexture(Image);
}





