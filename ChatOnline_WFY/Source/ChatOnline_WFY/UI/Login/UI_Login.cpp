
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Login.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "UI_LoginMain.h"
#include "Components/TextBlock.h"
#include "../Core/UI_CoreMacro.h"
#include "ThreadManage.h"
#include "../../MobyGameType.h"
//#include <Engine/Engine.h>
#include <Kismet/GameplayStatics.h>

void UUI_Login::BindClientRcv()
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

void UUI_Login::NativeConstruct()
{
	Super::NativeConstruct();

	SignInButton->OnReleased.AddDynamic(this, &UUI_Login::SignInGame);
	SignUpButton->OnReleased.AddDynamic(this, &UUI_Login::SignUpGame);

	//循环绑定 指导成功为止
	BindClientRcv();
}

void UUI_Login::NativeDestruct()
{
	Super::NativeDestruct();
}

bool UUI_Login::IsAccountValid()
{
	bool bIsValid = false;

	if (Account)
	{
		if (Account->GetText().ToString().Len() >= 6)
		{
			bIsValid = true;
		}
		else
		{
			LoginMsg("Accounts need to be greater than or equal to 6 bits.");
		}
	}
	else
	{
		LoginMsg("Account Instance non-existent.");
	}

	return bIsValid;
}

bool UUI_Login::IsPasswordValid()
{
	bool bIsValid = false;

	if (Password)
	{
		if (Password->GetText().ToString().Len() >= 6)
		{
			bIsValid = true;
		}
		else
		{
			LoginMsg("Password need to be greater than or equal to 6 bits.");
		}
	}
	else
	{
		LoginMsg("Password Instance non-existent.");
	}

	return bIsValid;
}

void UUI_Login::LoginCallback()
{
	//openLevel
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("150.158.18.192:7777")));
	//UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("127.0.0.1")));

	//向服务端发送信息验证,通过后进入服务器列表状态
	/*if (1)
	{
		if (GetParents<UUI_LoginMain>())
		{
			GetParents<UUI_LoginMain>()->CloseLoginUI();
		}
	}*/
}

void UUI_Login::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
	case SP_LoginSuccess:
	{
		LoginCallback();
		TArray<FGateInfo> GateInfos;

		SIMPLE_PROTOCOLS_RECEIVE(SP_LoginSuccess, GateInfos);

		LoginMsg(TEXT("LoginSuccess"));

		//初始化服务器列表
		//GetParents<UUI_LoginMain>()->AddSeverList(0, GateInfos);

		//释放自己
		/*if (Channel)
		{
			Channel->DestroySelf();
		}*/
		break;
	}
	case SP_LoginFailed:
	{
		LoginMsg(TEXT("Login failed~"));
		break;
	}
	case SP_Unregistered:
	{
		LoginMsg(TEXT("unregistered~"));
		break;
	}
	case SP_WrongPassword:
	{
		LoginMsg(TEXT("Wrong password~"));
		break;
	}
	case SP_RegisteredSuccess:
	{
		LoginMsg(TEXT("RegisteredSuccess"));
		break;
	}
	}
}

void UUI_Login::SignInGame()
{
	bool bIsValid = false;

	if (IsAccountValid())
	{
		if (IsPasswordValid())
		{
			FString AccountString = Account->GetText().ToString();
			FString PasswordString = Password->GetText().ToString();
			SEND_DATA(SP_Login, AccountString, PasswordString)

			return;
		}
	}

	//播放摇头动画
	// play the shaking head animation.
	//PlayAnimation(GetNameWidgetAnimation(TEXT("TipAnimation")));
}

void UUI_Login::SignUpGame()
{
	if (GetParents<UUI_LoginMain>())
	{
		GetParents<UUI_LoginMain>()->OpenRegisterUI();
	}
}

void UUI_Login::LoginMsg(FString Mes)
{
	if (TipText)
	{
		TipText->SetText(FText::FromString(Mes));
	}
}
