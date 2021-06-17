// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginRegisterInterface.h"
#include "Engine.h"

#include <string>

#define LOCTEXT_NAMESPACE "ULoginRegisterInterface"

void ULoginRegisterInterface::PostInitProperties()
{
	Super::PostInitProperties();

	Link = MakeShareable(new FSimpleMysqlLink(InUser, InHost, InPawd, InDB, InPort, Unix_Socket, InClientFlag));

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

	UserLandManager->GetUserDataManagerTool().setSqlLink(Link.ToSharedRef());
}

void ULoginRegisterInterface::ShowOrCreateOneWidget(UWidget* SelfWidget, TSubclassOf<UUserWidget> MyUserWidget)
{

}


bool ULoginRegisterInterface::OnPhoneNumberCommit(FText PhoneNumber, bool IsLoginInterface)
{

	return false;
}

bool ULoginRegisterInterface::OnInputPasswordCommit(FText Password)
{

	return false;
}

bool ULoginRegisterInterface::OnInputUserNameCommit(FText UserName)
{

	return false;
}

bool ULoginRegisterInterface::OnClickGetVerificationButton()
{

	return false;
}

void ULoginRegisterInterface::OnClickExistLoginButton()
{

}

bool ULoginRegisterInterface::OnClickPasswordLoginButton()
{
	return false;
}

void ULoginRegisterInterface::SetTheButtonIsEnable(FString ButtonType)
{

}

void ULoginRegisterInterface::SetForgetPasswordColor()
{

}

bool ULoginRegisterInterface::OnClickCodeLoginButton()
{



	//UserLandManager->TryRegisterOneUser();


	return false;
}

bool ULoginRegisterInterface::OnClickRegisterButton()
{
	Print_F("OnClickRegisterButton");

	if (!UserLandManager)
	{
		return false;
	}

	FString Err1;
	FDMUserData OneUserData1;
	UserLandManager->RegisterUser(OneUserData1, "123456", "0000", Err1);

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

}

bool ULoginRegisterInterface::JudgePasswordEquality()
{
	return false;
}

bool ULoginRegisterInterface::OnUserSecondCommitPassword(FText SecondPassword)
{
	return false;
}

bool ULoginRegisterInterface::OnClickConfirmModifyButton()
{
	return false;
}

void ULoginRegisterInterface::SetCodeButtonColorAndActive()
{

}

void ULoginRegisterInterface::SetCodeButtonCanNotClick()
{

}

void ULoginRegisterInterface::SetCodeButtonCanClick()
{

}

void ULoginRegisterInterface::ShowCurrentUserName()
{

}

bool ULoginRegisterInterface::GetIsInUserLand()
{
	return false;
}

/*-------------------------------------------*/

bool ULoginRegisterInterface::QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug)
{

	Link->QueryLinkResult(SQL, Results, ErrMesg, SaveType, Debug);

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

	Link->InsertTableData(TableName, KeyValueDatas, QueryParameters, ErrorMsg);

	return false;
}
#undef LOCTEXT_NAMESPACE