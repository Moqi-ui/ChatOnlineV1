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
//#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Math.h"
//#include "../Common/UI_TopTitle.h"

void UUI_GamingPage::NativeConstruct()
{
	Super::NativeConstruct();

	GamingMenuButton->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickMenuButton);
	Mic->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickMicButton);
	Speaker->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickSpeakerButton);
	EarToReturnButton->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickEarToReturnButton);
	RoomPageButton->OnClicked.AddDynamic(this, &UUI_GamingPage::SwitchRoomPage);
	VoicePageButton->OnClicked.AddDynamic(this, &UUI_GamingPage::SwitchVoicePage);
	SetingPageButton->OnClicked.AddDynamic(this, &UUI_GamingPage::SwitchSettingPage);
	ExitRoom->OnClicked.AddDynamic(this, &UUI_GamingPage::RequestExitRoom);
	ExitGame->OnClicked.AddDynamic(this, &UUI_GamingPage::RequestExitGame);
	ReturnGmaing->OnClicked.AddDynamic(this, &UUI_GamingPage::ReturnGaming);
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
			if (!RoomID.IsEmpty())
			{
				RoomID = Instance->GetCurrentRoomInfo();
				RoomID.Split("/", nullptr, &RoomID);
				RoomID.Split("/", nullptr, &RoomID);
			}
		}

		int uid = rand() % 10000 + 10000;
		BaseVoiceControl->TrySetRangeAudioTeamID(uid);
		BaseVoiceControl->TrySetRangeAudioMode();
		BaseVoiceControl->EnterRoom(RoomID, ITMG_ROOM_TYPE::ITMG_ROOM_TYPE_FLUENCY);

		/*GetCurrentPawn<AChatOnline_WFYCharacter>()
		和Cast<AChatOnline_WFYCharacter>(GetWorld()->GetPlyaerController()->GetPawn());等效，前者为模板运用*/
		//AChatOnline_WFYCharacter* InCharacterGaming = GetCurrentPawn<AChatOnline_WFYCharacter>();
		//if (InCharacterGaming)
		//{
		//	FString UserName = Instance->GetUserInfo().userName;
		//	//InCharacterGaming->GetTopTitle()->SetTitle(UserName);
		//}
	}

	BindClientRcv();
}

void UUI_GamingPage::NativeDestruct()
{
	Super::NativeDestruct();


}

void UUI_GamingPage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (BaseVoiceControl && GetWorld())
	{
		//Get
		FString msg;
		FVector location = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		FRotator Rotator = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorRotation();
		BaseVoiceControl->UpdatePosition(location, Rotator, msg);

		int32 eventId = BaseVoiceControl->GetUserState();
		UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

		switch (eventId)
		{
			case ITMG_EVENT_ID_USER_ENTER:
			{
				PlayerUpdateDebug->SetText(FText::FromString("UserEnter"));
				break;
			}
			case ITMG_EVENT_ID_USER_EXIT:
			{
				PlayerUpdateDebug->SetText(FText::FromString("UserExit"));
				break;
			}
			case ITMG_EVENT_ID_USER_HAS_AUDIO:
			{
				Instance->SetUserSpeakerState(true);
				PlayerUpdateDebug->SetText(FText::FromString("UserSpeaking"));
				break;
			}
			case ITMG_EVENT_ID_USER_NO_AUDIO:
			{
				//有成员停止发送音频包
				PlayerUpdateDebug->SetText(FText::FromString("UserNOSpeake"));
				Instance->SetUserSpeakerState(false);
				break;
			}
		}

		PlayerLocationDebug->SetText(FText::FromString(msg));
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "TestTick");
	}
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

			if (bIsExitGame)
			{
				GetWorld()->GetFirstPlayerController()->ConsoleCommand("QUIT");
			}
			else
			{
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("ThirdPersonExampleMap"));
			}
			break;
		}
		case SP_GetPlayerNumberResult:
		{
			FString CurrentPlayerNumber;

			SIMPLE_PROTOCOLS_RECEIVE(SP_GetPlayerNumberResult, CurrentPlayerNumber);

			UpdateRoomInfo(CurrentPlayerNumber);

			break;
		}
	}
}

void UUI_GamingPage::OnClickMenuButton()
{
	GameMenuPage->SetVisibility(ESlateVisibility::Visible);

	//FInputModeUIOnly inputModeUIOnly;

	//TSharedPtr<SWidget>

	//inputModeUIOnly.SetWidgetToFocus(this);

	//GetWorld()->GetFirstPlayerController()->SetInputMode(inputModeUIOnly);
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

void UUI_GamingPage::SwitchRoomPage()
{
	FString Key_RoomName;

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	if (Instance)
	{
		Key_RoomName = Instance->GetCurrentRoomInfo();

		SEND_DATA_GAME(SP_GetCurrentRoomPlayers, Key_RoomName);
	}

	GameSwitchPage->SetActiveWidgetIndex(0);
}
void UUI_GamingPage::SwitchVoicePage()
{
	GameSwitchPage->SetActiveWidgetIndex(1);
}
void UUI_GamingPage::SwitchSettingPage()
{
	GameSwitchPage->SetActiveWidgetIndex(2);
}
void UUI_GamingPage::RequestExitRoom()
{
	FString Key_RoomName;

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	if (Instance)
	{
		Key_RoomName = Instance->GetCurrentRoomInfo();

		SEND_DATA_GAME(SP_RequestExitRoom, Key_RoomName);
	}
}
void UUI_GamingPage::RequestExitGame()
{
	FString Key_RoomName;

	bIsExitGame = true;

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	if (Instance)
	{
		Key_RoomName = Instance->GetCurrentRoomInfo();

		SEND_DATA_GAME(SP_RequestExitRoom, Key_RoomName);
	}

}
void UUI_GamingPage::ReturnGaming()
{
	GameMenuPage->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_GamingPage::UpdateRoomInfo(FString CurrentPlayerNumber)
{
	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());
	if (Instance)
	{
		FString RoomInfo, RoomName, RoomID;

		RoomInfo = Instance->GetCurrentRoomInfo();

		RoomInfo.Split("/",nullptr, &RoomInfo);

		RoomInfo.Split("/", &RoomName, &RoomID);

		TextRoomName->SetText(FText::FromString(RoomName));

		TextRoomID->SetText(FText::FromString(RoomID));

		TextPlyaerNumber->SetText(FText::FromString(CurrentPlayerNumber+"/20"));
	}
}
