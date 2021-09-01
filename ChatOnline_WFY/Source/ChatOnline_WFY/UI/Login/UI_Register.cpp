// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Register.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI_LoginMain.h"
#include "Components/TextBlock.h"
#include "../../Login/LoginPawn.h"
#include "ThreadManage.h"
#include "../../Protocols/LoginProtocols.h"
#include "../Core/UI_CoreMacro.h"

void UUI_Register::NativeConstruct()
{
	Super::NativeConstruct();

	RandNameButton->OnReleased.AddDynamic(this, &UUI_Register::RandPlayerName);
	SendButton->OnReleased.AddDynamic(this, &UUI_Register::SendPlayerRegisterToServer);
	TurnOffButton->OnReleased.AddDynamic(this, &UUI_Register::TurnOffRegisterUI);

	BindClientRcv();
}

void UUI_Register::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_Register::RandPlayerName()
{
	//FontScriptLib ScriptLib;
	//FString PlayerName;

	//FString NameText = ScriptLib.EnglishFont.ToString();

	////随机名 长度
	////random name length
	//int32 IntRand = FMath::RandRange(7, 20);
	//for (int32 i = 0;i < IntRand ; i++)
	//{
	//	PlayerName += NameText[FMath::RandRange(0, NameText.Len() - 1)];
	//}

	//NickName->SetText(FText::FromString(PlayerName));
}

void UUI_Register::BindClientRcv()
{
	if (ALoginPawn* InPawn = GetCurrentPawn<ALoginPawn>())
	{
		if (InPawn->GetClient())
		{
			InPawn->GetClient()->GetController()->RecvDelegate.AddLambda([this](uint32 ProtocolNumber, FSimpleChannel* Channel)
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

void UUI_Register::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
		case SP_RegisteredSuccess:
		{
			TurnOffRegisterUI();
			SetNewMess("Registered successful.");
			break;
		}
		case SP_AccountRepetition:
		{
			SetNewMess("Duplicate account found in registration verification.");
			break;
		}
		case SP_NameRepetition:
		{
			SetNewMess("Duplicate player name found in registration verification.");
			break;
		}
		case SP_ServerError:
		{
			SetNewMess("Server Error.");
			break;
		}
	}
}

void UUI_Register::SendPlayerRegisterToServer()
{
	//注册信息
	FString NickNameString = NickName->GetText().ToString();
	FString AccountString = Account->GetText().ToString();
	FString PasswordString = Password->GetText().ToString();
	if (AccountString.Len() >= 6)
	{
		if (PasswordString.Len() >= 6)
		{
			SEND_DATA(SP_Registered, NickNameString, AccountString, PasswordString)
			SetNewMess("");
		}
		else
		{
			SetNewMess("The password must be at least 6 digits.");
		}
	}
	else
	{
		SetNewMess("The account must be at least 6 digits.");
	}
}

bool UUI_Register::CheckNameToServer()
{
	return false;
}

void UUI_Register::TurnOffRegisterUI()
{
	if (GetParents<UUI_LoginMain>())
	{
		GetParents<UUI_LoginMain>()->CloseRegisterUI();
	}
}

void UUI_Register::SetNewMess(const FString& NewMess)
{
	if (Messl)
	{
		Messl->SetText(FText::FromString(NewMess));
	}
}
