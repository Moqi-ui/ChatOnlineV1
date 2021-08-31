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
	//��������ؼ�
	if (SelfWidget)
	{
		SelfWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	TArray<UUserWidget*> T_AllWidget;

	if (GetWorld())
	{
		//����
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
	//����ֻ��Ÿ�ʽ����ȷ����û��ע�������ִ�е�������¼����ť����߼���by moqi 20190925 
	UserInputNumber = PhoneNumber.ToString();

	if (!UserLandManager)
	{
		return false;
	}
	//by moqi 20191017
	UserLandManager->CurrentInputPhnoeNumber = UserInputNumber;

	if (UserLandManager->JudgePhoneNumberFormat(UserInputNumber))
	{
		//�ж��ֻ����ǲ��Ǵ���
		if (UserLandManager->JudgePhoneNumberFIsRegister(UserInputNumber))
		{
			//�ж��ǲ��ǵ�¼���棨����ǣ��ֻ���ûע�������ʾ���ֻ���δע�᣻�����ע����棬�ֻ���ע�������ʾ���ֻ�����ע����ֱ�ӵ�¼��
			if (IsLoginInterface)
			{
				//����ǵ�¼���棬��ע��������жϵ�¼״̬��
				if (UserLandManager->GetLoginStatus(UserInputNumber) == 1)
				{
					if (UserLandManager->JudgeAccidentEixt(UserInputNumber))
					{
						//����������˳����������¼
						IsPhoneNumberFormat = true;
						PromptWordsState = ESlateVisibility::Hidden;
						//�������������밴ť
						ForgetPasswordButton = true;
						return true;
					}
					else
					{
						//����1����Ϊ����״̬�������ظ���¼
						IsPhoneNumberFormat = false;
						PromptWordsState = ESlateVisibility::Visible;
						PromptWords = LOCTEXT("OnlineStatus", "���û��ѵ�¼");
						ForgetPasswordButton = false;
						return false;
					}
				}
				else
				{
					//�����������״̬�� ����Ե�¼
					IsPhoneNumberFormat = true;
					//�������������밴ť
					ForgetPasswordButton = true;
					PromptWordsState = ESlateVisibility::Hidden;
					return true;
				}
			}
			else
			{
				PromptWordsState = ESlateVisibility::Visible;
				PromptWords = LOCTEXT("PhoneNumberisRegister", "�ֻ�����ע�ᣬ��ֱ�ӵ�¼");
				IsPhoneNumberFormat = false;
				return false;
			}
		}
		else
		{
			//����������������
			ForgetPasswordButton = false;

			if (IsLoginInterface)
			{
				//������ʾ��ֻ���δע��
				PromptWordsState = ESlateVisibility::Visible;
				//PromptWords = LOCTEXT("PhoneNumberNotRegister1", " �ֻ���δע�ᣬ����ע�� ");
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
		//������ʾ��ֻ��Ÿ�ʽ����ȷ
		IsPhoneNumberFormat = false;

		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("FormatNotRight", "�ֻ��Ÿ�ʽ����ȷ");

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
	PromptWords = LOCTEXT("PassWordFormatNotRight", "�����ʽ����ȷ");

	return false;
}
//#pragma optimize("",off)
bool ULoginRegisterInterface::OnClickPasswordLoginButton()
{
	//Print_F("OnClickPasswordLoginButton");

	if (!UserLandManager)
	{
		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("LoginFilea", " ��¼ʧ�� ");

		return false;
	}

	FString Err_;

	if (UserLandManager->TryLandFromPassword("phone", UserInputNumber, UserInputPassword, Err_))
	{
		FText temp = LOCTEXT("propmt1", "�����¼�ɹ�!");
		Print_F(temp.ToString());
		return true;
	}

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("PassWordorphonenotRight", "�ֻ��Ż����벻��ȷ");

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
	PromptWords = LOCTEXT("VerificationCodeFormatNotRight", "��֤���ʽ����ȷ������������");


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
	PromptWords = LOCTEXT("UserNameFormatNotRight", "������ʽ����ȷ������������");

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

		FText temp = LOCTEXT("propmt", "��֤���¼�ɹ�!");

		Print_F(temp.ToString());

		PromptWordsState = ESlateVisibility::Hidden;


		return true;
	}

	PromptWordsState = ESlateVisibility::Visible;
	PromptWords = LOCTEXT("VerificationFormat", "�ֻ��Ż���֤�벻��ȷ");

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
			//ע��ɹ�
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("RegisterSuccessful", "ע��ɹ�,������ת����¼ҳ��...");
			return true;
		}
		else
		{
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("UnknowFaile", " ע��ʧ�����Ժ����� ");
			return false;
		}
	}
	else
	{
		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("VerificationCodeNotRight", "��֤����Ч������������");
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
	PromptWords = LOCTEXT("PasswordNotEquality", "�������벻һ��");

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
	PromptWords = LOCTEXT("PassWordFormatNotRight", "�����ʽ����ȷ");

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
			PromptWords = LOCTEXT("PasswordMModifySuccessful", "�����޸ĳɹ�,�����µ�¼");
			return true;
		}
		else if (Err_ == "TwopasswordEquality")
		{
			PromptWordsState = ESlateVisibility::Visible;
			PromptWords = LOCTEXT("PasswordMModifyfaile1", " �����벻�ܺ�ԭ������� ");
			return false;
		}

		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("PasswordMModifyfaile", " �����޸�ʧ�ܣ��Ժ����� ");
		return false;
	}
	else
	{
		PromptWordsState = ESlateVisibility::Visible;
		PromptWords = LOCTEXT("VerificationNotval", "��֤����Ч����������");
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