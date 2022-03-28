
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Login.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "UI_LoginMain.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "../Core/UI_CoreMacro.h"
#include "ThreadManage.h"
#include "../../MobyGameType.h"
#include <Kismet/GameplayStatics.h>
#include "Gaming/COL_SaveGame.h"
#include "Gaming/ChatOnLine_GameInstance.h"
#define LOCTEXT_NAMESPACE "UUI_Login"

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
	Eye_ShowPassword->OnPressed.AddDynamic(this,&UUI_Login::ShowPassWord);
	Eye_ShowPassword->OnReleased.AddDynamic(this, &UUI_Login::HidePassWord);
	ExitGame->OnReleased.AddDynamic(this, &UUI_Login::TryExitGame);
	//SaveButton->OnReleased.AddDynamic(this, &UUI_Login::SaveGame);
	//LoadButton->OnReleased.AddDynamic(this, &UUI_Login::LoadGame);
	//循环绑定 指导成功为止
	BindClientRcv();
	LoadGame();
}

void UUI_Login::NativeDestruct()
{
	Super::NativeDestruct();
}

bool UUI_Login::IsAccountValid()
{
	bool bIsValid = false;

	if (Account->GetText().ToString().Len() >= 6)
	{
		bIsValid = true;
	}
	else
	{
		FText text = FText(LOCTEXT("myText", "账号长度少于6位"));
		LoginMsg(text);
	}

	return bIsValid;
}

bool UUI_Login::IsPasswordValid()
{
	bool bIsValid = false;

	if (Password->GetText().ToString().Len() >= 6)
	{
		bIsValid = true;
	}
	else
	{
		FText text = FText(LOCTEXT("myText", "密码长度少于6位"));
		LoginMsg(text);
	}

	return bIsValid;
}

void UUI_Login::LoginCallback(FString UserInfo)
{
	FText text = FText(LOCTEXT("myText", "登录成功，正在进入···"));
	LoginMsg(text);
	SaveGame();
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("ThirdPersonExampleMap")));

	UChatOnLine_GameInstance* GameInstance = Cast<UChatOnLine_GameInstance>(GetGameInstance());

	FUserInfo userInfo;

	userInfo.userName = UserInfo;

	GameInstance->SetUserInfo(userInfo);

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
			TArray<FGateInfo> GateInfos;
			FString userName;
			SIMPLE_PROTOCOLS_RECEIVE(SP_LoginSuccess, userName, GateInfos);
			LoginCallback(userName);
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
			//LoginMsg(TEXT("df"));
			FText text = FText(LOCTEXT("myText", "登录失败"));
			LoginMsg(text);
			break;
		}
		case SP_Unregistered:
		{
			FText text = FText(LOCTEXT("myText", "手机号未注册"));
			LoginMsg(text);
			break;
		}
		case SP_WrongPassword:
		{
			FText text = FText(LOCTEXT("myText", "密码错误"));
			LoginMsg(text);
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
void UUI_Login::ShowPassWord()
{
	FButtonStyle style;
	FSlateBrush Buresh;
	auto ddd = Buresh.GetResourceName();
	//style.SetNormal();
	//Eye_ShowPassword->SetStyle();
	Password->SetIsPassword(false);
}

void UUI_Login::HidePassWord()
{
	Password->SetIsPassword(true);
}

void UUI_Login::TryExitGame()
{
	//UGameplayStatics::com
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("QUIT");
}

void UUI_Login::LoginMsg(FText Mes)
{
	if (TipText)
	{
		TipText->SetVisibility(ESlateVisibility::Visible);
		TipText->SetText(Mes);
	}
}
void UUI_Login::SaveGame()
{
	if (UCOL_SaveGame* SaveGameInstance = Cast<UCOL_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCOL_SaveGame::StaticClass())))
	{
		// 设置savegame对象上的数据。
		SaveGameInstance->PlayerAccount = Account->GetText().ToString();
		bIsRemberMe = bIsRemberPassword->IsChecked();
		if (bIsRemberMe)
		{
			SaveGameInstance->PlayerPassword = Password->GetText().ToString();

			SaveGameInstance->bIsRemberMe = bIsRemberMe;
		}

		// 即时保存游戏。
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0);
	}
}
void UUI_Login::LoadGame()
{
	// 检索并将USaveGame对象投射到UMySaveGame。
	if (UCOL_SaveGame* LoadedGame = Cast<UCOL_SaveGame>(UGameplayStatics::LoadGameFromSlot("LoginSaveSlot", 0)))
	{
		Account->SetText(FText::FromString(LoadedGame->PlayerAccount));
		Password->SetText(FText::FromString(LoadedGame->PlayerPassword));
		if (LoadedGame->bIsRemberMe)
		{
			bIsRemberPassword->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{
			bIsRemberPassword->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}
#undef LOCTEXT_NAMESPACE