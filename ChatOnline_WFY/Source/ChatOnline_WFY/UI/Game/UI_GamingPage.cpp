// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GamingPage.h"
#include "Button.h"
#include "ChatOnline_WFYCharacter.h"

#include "../Core/UI_CoreMacro.h"
#include "ThreadManage.h"
#include <Kismet/GameplayStatics.h>
#include "Gaming/ChatOnLine_GameInstance.h"

void UUI_GamingPage::NativeConstruct()
{
	Super::NativeConstruct();

	GamingMenuButton->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickMenuButton);
	Mic->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickMicButton);
	Speaker->OnClicked.AddDynamic(this, &UUI_GamingPage::OnClickSpeakerButton);


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
		case SP_LoginFailed:
		{

			break;
		}
	}
}





void UUI_GamingPage::OnClickMenuButton()
{
	FString Key_RoomName;

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	int ii = Instance->GetCurrentPlayerNumbers();

	if (ii == 1)
	{
		Key_RoomName = Instance->GetCurrentRoomInfo();

		//SEND_DATA_GAME(SP_TryDestroyRoom, Key_RoomName);
	}
}

void UUI_GamingPage::OnClickMicButton()
{

}

void UUI_GamingPage::OnClickSpeakerButton()
{

}