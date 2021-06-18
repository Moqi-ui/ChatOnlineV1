// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginRegisterInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine.h"

#include <string>

#define LOCTEXT_NAMESPACE "ULoginRegisterInterface"

void ULoginRegisterInterface::PostInitProperties()
{
	Super::PostInitProperties();

	//Link = MakeShareable(new FSimpleMysqlLink(InUser, InHost, InPawd, InDB, InPort, Unix_Socket, InClientFlag));

	//Print_F("PostInitProperties");
	//GLog->Log();
	UE_LOG(LogTemp, Log, TEXT("PostInitProperties"));
}

void ULoginRegisterInterface::Print_F(FString InputStr)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, InputStr);
}

void ULoginRegisterInterface::init()
{
	UserLandManager = FUserLandManager::Get();

	//UserLandManager->GetUserDataManagerTool().setSqlLink(Link.ToSharedRef());
}

void ULoginRegisterInterface::AddUMGToScreen(TSubclassOf<UUserWidget> MyUserWidget)
{
	//by moqi 20190925
	if (GetWorld())
	{

		UUserWidget* pUserWidget;

		pUserWidget = CreateWidget<UUserWidget>(GetWorld(), MyUserWidget);

		if (pUserWidget)
		{
			pUserWidget->AddToViewport();
		}
	}
}

void ULoginRegisterInterface::ShowOrCreateOneWidget(UWidget* SelfWidget, TSubclassOf<UUserWidget> MyUserWidget)
{
	//隐藏自身控件
	if (SelfWidget)
	{
		SelfWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	TArray<UUserWidget*> T_AllWidget;

	if (GetWorld())
	{
		//遍历
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), T_AllWidget, MyUserWidget);

		if (T_AllWidget.Num() > 0)
		{
			if (T_AllWidget[0])
			{
				T_AllWidget[0]->SetVisibility(ESlateVisibility::Visible);

				Print_F("1");

				return;
			}
		}
		Print_F("0");
		AddUMGToScreen(MyUserWidget);
	}
}



bool ULoginRegisterInterface::OnPhoneNumberCommit(FText PhoneNumber, bool IsLoginInterface)
{
	Print_F("OnPhoneNumberCommit");
	//如果手机号格式不正确或者没有注册过，则不执行单击“登录”按钮后的逻辑。by moqi 20190925 
	UserInputNumber = PhoneNumber.ToString();

	if (!UserLandManager)
	{
		return false;
	}
	//by moqi 20191017
	UserLandManager->CurrentInputPhnoeNumber = UserInputNumber;

	if (UserLandManager->JudgePhoneNumberFormat(UserInputNumber))
	{
		//判断手机号是不是存在
		if (UserLandManager->JudgePhoneNumberFIsRegister(UserInputNumber))
		{
			//判断是不是登录界面（如果是，手机号没注册过就提示：手机号未注册；如果是注册界面，手机号注册过就提示：手机号已注册请直接登录）
			if (IsLoginInterface)
			{
				//如果是登录界面，且注册过，则判断登录状态，
				if (UserLandManager->GetLoginStatus(UserInputNumber) == 1)
				{
					if (UserLandManager->JudgeAccidentEixt(UserInputNumber))
					{
						//如果是意外退出，则允许登录
						IsPhoneNumberFormat = true;
						PromptWordsState = ESlateVisibility::Hidden;
						//允许点击忘记密码按钮
						ForgetPasswordButton = true;
						return true;
					}
					else
					{
						//返回1，则为在线状态，不能重复登录
						IsPhoneNumberFormat = false;
						PromptWordsState = ESlateVisibility::Visible;
						PromptWords = LOCTEXT("OnlineStatus", "此用户已登录");
						ForgetPasswordButton = false;
						return false;
					}
				}
				else
				{
					//如果不是在线状态， 则可以登录
					IsPhoneNumberFormat = true;
					//允许点击忘记密码按钮
					ForgetPasswordButton = true;
					PromptWordsState = ESlateVisibility::Hidden;
					return true;
				}
			}
			else
			{
				PromptWordsState = ESlateVisibility::Visible;
				PromptWords = LOCTEXT("PhoneNumberisRegister", "手机号已注册，请直接登录");
				IsPhoneNumberFormat = false;
				return false;
			}
		}
		else
		{
			//不允许点击忘记密码
			ForgetPasswordButton = false;

			if (IsLoginInterface)
			{
				//设置提示语：手机号未注册
				PromptWordsState = ESlateVisibility::Visible;
				//PromptWords = LOCTEXT("PhoneNumberNotRegister1", " 手机号未注册，请先注册 ");
				IsPhoneNumberFormat = false;
				return false;
			}
			else
			{
				PromptWordsState = ESlateVisibility::Hidden;
				IsPhoneNumberFormat = true;
				return true;
			}
		}
	}
	else
	{
		//设置提示语：手机号格式不正确
		IsPhoneNumberFormat = false;

		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("FormatNotRight", "手机号格式不正确");

		return false;
	}
}
bool ULoginRegisterInterface::OnInputPasswordCommit(FText Password)
{
	Print_F("OnInputPasswordCommit");

	// by moqi 20190926

	UserInputPassword = Password.ToString();

	if (!UserLandManager)
	{
		return false;
	}

	if (UserLandManager->JudgePasswordFormat(UserInputPassword))
	{
		IsPasswordFormat = true;
		PromptWordsState = ESlateVisibility::Hidden;
		return true;
	}

	IsPasswordFormat = false;

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("PassWordFormatNotRight", "密码格式不正确");

	return false;
}
//#pragma optimize("",off)
bool ULoginRegisterInterface::OnClickPasswordLoginButton()
{
	//Print_F("OnClickPasswordLoginButton");

	if (!UserLandManager)
	{
		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("LoginFilea", " 登录失败 ");

		return false;
	}

	FString Err_;

	if (UserLandManager->TryLandFromPassword("phone", UserInputNumber, UserInputPassword, Err_))
	{
		FText temp = LOCTEXT("propmt1", "密码登录成功!");
		Print_F(temp.ToString());
		return true;
	}

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("PassWordorphonenotRight", "手机号或密码不正确");

	return false;
}
//#pragma optimize("",on)

void ULoginRegisterInterface::SetTheButtonIsEnable(FString ButtonType)
{

	if (ButtonType == "PasswordLogin")
	{
		if (IsPhoneNumberFormat && IsPasswordFormat)
		{
			TheButtonBGColor = FLinearColor(1, 0.082283, 0.082283, 1);
			TheButtonIsEnable = true;
		}
		else
		{
			TheButtonBGColor = FLinearColor(0.317647, 0.317647, 0.317647, 1);

			TheButtonIsEnable = false;
		}
	}
	else if (ButtonType == "VerificationCodeLogin")
	{
		if (IsPhoneNumberFormat && IsVerificationCodeFormat)
		{
			TheButtonBGColor = FLinearColor(1, 0.082283, 0.082283, 1);
			TheButtonIsEnable = true;
		}
		else
		{
			TheButtonBGColor = FLinearColor(0.317647, 0.317647, 0.317647, 1);

			TheButtonIsEnable = false;
		}
	}
	else if (ButtonType == "RegisterButton")
	{
		if (IsPhoneNumberFormat && IsVerificationCodeFormat && IsUserNameFormat && IsPasswordFormat)
		{
			TheButtonBGColor = FLinearColor(1, 0.082283, 0.082283, 1);
			TheButtonIsEnable = true;
		}
		else
		{
			TheButtonBGColor = FLinearColor(0.317647, 0.317647, 0.317647, 1);

			TheButtonIsEnable = false;
		}
	}
	else if (ButtonType == "ModifyPassword")
	{
		if (IsVerificationCodeFormat && IsPasswordFormat && IsPasswordEquality)
		{
			TheButtonBGColor = FLinearColor(1, 0.082283, 0.082283, 1);
			TheButtonIsEnable = true;
		}
		else
		{
			TheButtonBGColor = FLinearColor(0.317647, 0.317647, 0.317647, 1);

			TheButtonIsEnable = false;
		}

	}

	else
	{
		return;
	}

}

void ULoginRegisterInterface::SetForgetPasswordColor()
{
	if (ForgetPasswordButton)
	{
		ForgetTextColor = FLinearColor(1, 0.082283, 0.082283, 1);
	}
	else
	{
		ForgetTextColor = FLinearColor(0, 0, 0, 0.3);
	}
}



bool ULoginRegisterInterface::OnInputVerificationCodeCommit(FText Code)
{
	Print_F("OnInputVerificationCodeCommit");

	//by moqi 20190926
	UserInputVerification = Code.ToString();

	if (!UserLandManager)
	{
		return false;
	}

	if (UserLandManager->JudgeVerificationCodeFormat(UserInputVerification))
	{
		IsVerificationCodeFormat = true;

		PromptWordsState = ESlateVisibility::Hidden;

		return true;
	}

	IsVerificationCodeFormat = false;

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("VerificationCodeFormatNotRight", "验证码格式不正确，请重新输入");


	return false;
}
bool ULoginRegisterInterface::OnInputUserNameCommit(FText UserName)
{
	Print_F("OnInputUserNameCommit");

	//by moqi 20190926
	UserInputName = UserName.ToString();

	if (!UserLandManager)
	{
		return false;
	}

	if (UserLandManager->JudgeUserNameFormat(UserInputName))
	{
		IsUserNameFormat = true;

		PromptWordsState = ESlateVisibility::Hidden;

		return true;
	}
	IsUserNameFormat = false;

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("UserNameFormatNotRight", "姓名格式不正确，请重新输入");

	return false;
}

bool ULoginRegisterInterface::OnClickGetVerificationButton()
{
	Print_F("OnClickGetVerificationButton");

	if (!UserLandManager)
	{
		return false;
	}

	FString Err;


	if (UserLandManager->MakeNewVerificationCode("Phone", UserInputNumber, Err))
	{

		return true;
	}

	return false;
}

void ULoginRegisterInterface::OnClickExistLoginButton()
{
	if (!UserLandManager)
	{
		return;
	}

	UserLandManager->Logout();

}




bool ULoginRegisterInterface::OnClickCodeLoginButton()
{
	Print_F("OnClickCodeLoginButton");
	if (!UserLandManager)
	{
		return false;
	}
	FString Err_;
	if (UserLandManager->TryLandFromVerificationCode(UserInputNumber, UserInputVerification, Err_))
	{

		FText temp = LOCTEXT("propmt", "验证码登录成功!");

		Print_F(temp.ToString());

		PromptWordsState = ESlateVisibility::Hidden;


		return true;
	}

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("VerificationFormat", "手机号或验证码不正确");

	return false;
}

bool ULoginRegisterInterface::OnClickRegisterButton()
{
	Print_F("OnClickRegisterButton");

	if (!UserLandManager)
	{
		return false;
	}

	FDMUserData OneUserData1;
	OneUserData1.userPhoneNumber = UserInputNumber;
	OneUserData1.userName = UserInputName;
	FString Err1;

	UserLandManager->RegisterUser(OneUserData1, UserInputPassword, UserInputVerification, Err1);

	return false;

	if (UserLandManager->VerificationCodeValidity(UserInputNumber, UserInputVerification))
	{
		FDMUserData OneUserData;
		OneUserData.userPhoneNumber = UserInputNumber;
		OneUserData.userName = UserInputName;

		FString Err;
		if (UserLandManager->RegisterUser(OneUserData, UserInputPassword, UserInputVerification, Err))
		{
			//注册成功
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("RegisterSuccessful", "注册成功,正在跳转到登录页面...");
			return true;
		}
		else
		{
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("UnknowFaile", " 注册失败请稍后重试 ");
			return false;
		}
	}
	else
	{
		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("VerificationCodeNotRight", "验证码无效，请重新输入");
		return false;
	}
}
void ULoginRegisterInterface::OnModifyPasswordWidget()
{
	//by moqi 20190930
	if (!UserLandManager)
	{
		return;
	}
	UserInputNumber = UserLandManager->GetUserData().userPhoneNumber;

	if (UserInputNumber == "")
	{
		UserInputNumber = UserLandManager->CurrentInputPhnoeNumber;
	}

	CurrentUserPhoneNumber = FText::FromString(UserInputNumber);
}

bool ULoginRegisterInterface::JudgePasswordEquality()
{
	//by moqi 20190930
	if (UserInputPassword == SecondPassword)
	{
		IsPasswordEquality = true;

		PromptWordsState = ESlateVisibility::Hidden;

		return true;
	}

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("PasswordNotEquality", "两次密码不一致");

	IsPasswordEquality = false;

	return false;
}
bool ULoginRegisterInterface::OnUserSecondCommitPassword(FText secondPassword)
{
	//by moqi 20191001
	SecondPassword = secondPassword.ToString();

	if (!UserLandManager)
	{
		return false;
	}

	if (UserLandManager->JudgePasswordFormat(SecondPassword))
	{
		IsPasswordFormat = true;
		PromptWordsState = ESlateVisibility::Hidden;
		return true;
	}

	IsPasswordFormat = false;

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("PassWordFormatNotRight", "密码格式不正确");

	return false;

}



bool ULoginRegisterInterface::OnClickConfirmModifyButton()
{
	//by moqi 20190930
	if (!UserLandManager)
	{
		return false;
	}

	if (UserLandManager->VerificationCodeValidity(UserInputNumber, UserInputVerification))
	{
		FDMUserData CurrentUserData = UserLandManager->GetUserData();

		int Userid = CurrentUserData.userID;

		if (!UserLandManager->IsInUserLand())
		{

			Userid = UserLandManager->GetUserIDForIdentifer(UserInputNumber);
		}

		FString Err_;

		if (UserLandManager->ChangePassword(Userid, UserInputPassword, Err_))
		{
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("PasswordMModifySuccessful", "密码修改成功,请重新登录");
			return true;
		}
		else if (Err_ == "TwopasswordEquality")
		{
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("PasswordMModifyfaile1", " 新密码不能和原密码相等 ");
			return false;
		}

		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("PasswordMModifyfaile", " 密码修改失败，稍后重试 ");
		return false;
	}
	else
	{
		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("VerificationNotval", "验证码无效请重新输入");
		return false;
	}

}

void ULoginRegisterInterface::SetCodeButtonColorAndActive()
{
	if (IsPhoneNumberFormat)
	{
		CodeButtonBGColor = FLinearColor(1, 0.082283, 0.082283, 1);

		CodeButtonIsEnable = true;
	}
	else
	{
		CodeButtonBGColor = FLinearColor(0.317647, 0.317647, 0.317647, 1);

		CodeButtonIsEnable = false;
	}

}

void ULoginRegisterInterface::SetCodeButtonCanNotClick()
{

	CodeButtonBGColor = FLinearColor(0.317647, 0.317647, 0.317647, 1);

	CodeButtonIsEnable = false;

}


void ULoginRegisterInterface::SetCodeButtonCanClick()
{
	CodeButtonBGColor = FLinearColor(1, 0.082283, 0.082283, 1);

	CodeButtonIsEnable = true;
}
void ULoginRegisterInterface::ShowCurrentUserName()
{
	if (!UserLandManager)
	{
		return;
	}

	CurrentUserName = FText::FromString(UserLandManager->GetUserData().userName);
}
bool ULoginRegisterInterface::GetIsInUserLand()
{
	if (!UserLandManager)
	{
		return false;
	}
	return UserLandManager->IsInUserLand();
}





















/*-------------------------------------------*/

bool ULoginRegisterInterface::QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug)
{

	//Link->QueryLinkResult(SQL, Results, ErrMesg, SaveType, Debug);

	return false;
}

bool ULoginRegisterInterface::InsertTableDatasTest()
{

	//const FString& TableName, const TMap<FString, FString>& InsetKeyValueDatas, const FSimpleMysqlQueryParameters& QueryParam, FString& ErrorMsg, bool bIgnore = false

	FString TableName = "testTable";

	TMap<FString, FString> KeyValueDatas;

	KeyValueDatas.Add("Age", "24");
	KeyValueDatas.Add("Name", "Imrcao");
	KeyValueDatas.Add("Time", "2021-06-17 09:34:38");

	FSimpleMysqlQueryParameters QueryParameters;

	FString ErrorMsg;

	//Link->InsertTableData(TableName, KeyValueDatas, QueryParameters, ErrorMsg);

	return false;
}
#undef LOCTEXT_NAMESPACE