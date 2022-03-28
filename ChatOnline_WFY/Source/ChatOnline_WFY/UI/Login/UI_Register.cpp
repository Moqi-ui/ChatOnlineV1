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
//#include "SendSms.h"


void UUI_Register::NativeConstruct()
{
	Super::NativeConstruct();

	//GetVCodeBuuton->OnReleased.AddDynamic(this, &UUI_Register::RandPlayerName);
	RegisterButton->OnReleased.AddDynamic(this, &UUI_Register::SendPlayerRegisterToServer);
	ReturnMainPage->OnReleased.AddDynamic(this, &UUI_Register::TurnOffRegisterUI);
	GetVCodeBuuton->OnReleased.AddDynamic(this, &UUI_Register::TrySendVerification);
	LoginIn->OnReleased.AddDynamic(this, &UUI_Register::TurnOffRegisterUI);
	

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
			//TurnOffRegisterUI();
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
		case SP_GetVerificationSucceed:
		{
			FString code;
			SIMPLE_PROTOCOLS_RECEIVE(SP_GetVerificationSucceed, code);

			SendUserVerification = code;

			SetNewMess(code);

			break;
		}
	}
}

void UUI_Register::SendPlayerRegisterToServer()
{
	//判断输入的验证码是否正确
	if (!VerifyVerification())
	{
		SetNewMess("Verification input error");

		return;
	}

	//注册信息
	FString userName = UserName->GetText().ToString();
	FString userPhone = UserPhone->GetText().ToString();
	FString userPassword = UserPassword->GetText().ToString();
	//FString InputVerification = VerificationCode->GetText().ToString();

	if (userPhone.Len() >= 6)
	{
		if (userPassword.Len() >= 6)
		{
			SEND_DATA(SP_Registered, userName, userPhone, userPassword)
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

void UUI_Register::TrySendVerification()
{
	//注册信息
	FString userPhone = UserPhone->GetText().ToString();



	//countDown->SetText(LocalText);
	if (VerifyInputPhone(userPhone))
	{
		SEND_DATA(SP_TryGetVerification, userPhone)
		SetNewMess("");
	}
}

bool UUI_Register::VerifyVerification()
{
	FString inputVerification = VerificationCode->GetText().ToString();

	if (SendUserVerification == inputVerification)
	{
		return true;
	}
	return false;
}
bool UUI_Register::VerifyInputPhone(FString Phone)
{
	if (Phone.Len() != 11)
	{
		SetNewMess("Phone Format is not right");
		//SetNewMess("请输入十一位手机号");

		return false;
	}

	return true;
}

void UUI_Register::SetNewMess(const FString& NewMess)
{
	if (Prompt)
	{
		Prompt->SetText(FText::FromString(NewMess));
	}
}
