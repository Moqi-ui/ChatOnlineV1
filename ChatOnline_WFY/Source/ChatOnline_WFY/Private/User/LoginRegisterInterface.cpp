// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginRegisterInterface.h"
#include "Engine.h"

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
	userLandManger = FUserLandManager::Get();

	userLandManger->GetUserDataManagerTool().setSqlLink(Link);
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
	return false;
}

bool ULoginRegisterInterface::OnClickRegisterButton()
{
	return false;
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