// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GamingPage.h"
#include "Button.h"
#include "Image.h"
#include "ChatOnline_WFYCharacter.h"
#include "Engine/Engine.h"
#include "../Core/UI_CoreMacro.h"
#include "ThreadManage.h"
#include <Kismet/GameplayStatics.h>
#include "Gaming/ChatOnLine_GameInstance.h"
#include "BaseVoiceControlSystem.h"

void UUI_GamingPage::NativeConstruct()
{
	Super::NativeConstruct();

	GamingMenuButton->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickMenuButton);
	Mic->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickMicButton);
	Speaker->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickSpeakerButton);
	EarToReturnButton->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickEarToReturnButton);
	//加载Content目录下的资源文件
	//方法一：
	SpeackCheck = LoadObject<UTexture2D>(nullptr, TEXT("/Game/ChatOnline/WFY_Textture/Icon/Speaker_Check"));
	SpeackUncheck = LoadObject<UTexture2D>(nullptr, TEXT("/Game/ChatOnline/WFY_Textture/Icon/Speaker_Uncheck"));
	MicUncheck = LoadObject<UTexture2D>(nullptr, TEXT("/Game/ChatOnline/WFY_Textture/Icon/Mic_Uncheck"));

	//方法二
	FSoftObjectPath softObjectPath(TEXT("/Game/ChatOnline/WFY_Textture/Icon/Mic_check"));
	UObject* object = softObjectPath.TryLoad();
	MicCheck = Cast<UTexture2D>(object);

	//GME初始化
	BaseVoiceControl = NewObject<UBaseVoiceControlSystem>();
	if (BaseVoiceControl)
	{
		FString RoomID = "202101";
		BaseVoiceControl->InitGME();
		UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());
		if (Instance)
		{
			RoomID = Instance->GetCurrentRoomInfo();
			RoomID.Split("/", nullptr, &RoomID);
			RoomID.Split("/",nullptr, &RoomID);
		}
		BaseVoiceControl->EnterRoom(RoomID, ITMG_ROOM_TYPE::ITMG_ROOM_TYPE_FLUENCY);
	}

	BindClientRcv();
}

void UUI_GamingPage::NativeDestruct()
{
	Super::NativeDestruct();


}

void UUI_GamingPage::BindClientRcv()
{
	if (AChatOnline_WFYCharacter* InCharacterGaming = GetCurrentPawn<AChatOnline_WFYCharacter>())
	{
		if (InCharacterGaming->GetClient())
		{
			InCharacterGaming->GetClient()->GetController()->RecvDelegate.AddLambda([this](uint32 ProtocolNumber, FSimpleChannel* Channel)
				{
					this->RecvProtocol(ProtocolNumber, Channel);
				});
		}
		else
		{
			GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindClientRcv(); });
		}
	}
}

void UUI_GamingPage::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch(ProtocolNumber)
	{
		case SP_ExitRoom:
		{
			BaseVoiceControl->OnExitRoom();

			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("UChatOnLine_GameInstance::OnExitRoom()"));

			UGameplayStatics::OpenLevel(GetWorld(), TEXT("ThirdPersonExampleMap"));

			break;
		}
	}
}

void UUI_GamingPage::OnClickMenuButton()
{

	//BaseVoiceControl->OnExitRoom();
	//BaseVoiceControl->EnterRoom("202101", UserID, (ITMG_ROOM_TYPE)0);

	//BaseVoiceControl->EnterRoom("202101", UserID, ITMG_ROOM_TYPE::ITMG_ROOM_TYPE_FLUENCY);
	//BaseVoiceControl->OnExitRoom();
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("ThirdPersonExampleMap"));
	//退出房间
	FString Key_RoomName;

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	if (Instance)
	{
		Key_RoomName = Instance->GetCurrentRoomInfo();

		SEND_DATA_GAME(SP_GetCurrentRoomPlayers, Key_RoomName);
	}
}

void UUI_GamingPage::OnClickMicButton()
{
	if (BaseVoiceControl)
	{
		if (MicState)
		{
			Mic_Image->SetBrushFromTexture(MicUncheck, false);
			BaseVoiceControl->onCheckMic(false);
			MicState = false;
			UE_LOG(LogTemp, Warning, TEXT("OnClickMicButton--MicUncheck()"));
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnClickMicButton--MicUncheck"));
		}
		else
		{
			Mic_Image->SetBrushFromTexture(MicCheck, false);
			BaseVoiceControl->onCheckMic(true);
			MicState = true;
			UE_LOG(LogTemp, Warning, TEXT("OnClickMicButton--onCheckMic()"));
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnClickMicButton--onCheckMic"));
		}
	}
}

void UUI_GamingPage::OnClickSpeakerButton()
{
	if (BaseVoiceControl)
	{
		if (SpeakerState)
		{
			Speaker_Image->SetBrushFromTexture(SpeackUncheck, false);
			BaseVoiceControl->onCheckSpeaker(false);
			SpeakerState = false;
			UE_LOG(LogTemp, Warning, TEXT("OnClickSpeakerButton--SpeackUncheck()"));
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnClickSpeakerButton--SpeackUncheck"));
		}
		else
		{
			Speaker_Image->SetBrushFromTexture(SpeackCheck, false);
			BaseVoiceControl->onCheckSpeaker(true);
			SpeakerState = true;
			UE_LOG(LogTemp, Warning, TEXT("OnClickSpeakerButton--Speackcheck()"));
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnClickSpeakerButton--Speackcheck"));
		}
	}

}
void UUI_GamingPage::OnClickEarToReturnButton()
{
	if (BaseVoiceControl)
	{
		if (EarState)
		{
			BaseVoiceControl->EarToReturn(false);
			EarToReturn_Image->SetBrushFromTexture(SpeackCheck, false);
			EarState = false;
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnClickEarToReturnButton--Disable"));
		}
		else 
		{
			BaseVoiceControl->EarToReturn(true);
			EarToReturn_Image->SetBrushFromTexture(SpeackUncheck, false);
			EarState = true;
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("OnClickEarToReturnButton--Enable"));

		}
	}
}