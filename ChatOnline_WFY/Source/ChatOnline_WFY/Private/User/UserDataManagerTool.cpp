#include "UserDataManagerTool.h"



FUserDateManageTool::FUserDateManageTool()
{
	//UE_LOG(LogTemp, Log, TEXT("2222FUserDateManageTool()"));

	pDataBaseLinkName = MakeShareable(new FSimpleMysqlLink(InUser, InHost, InPawd, InDB, InPort, Unix_Socket, InClientFlag));


}

FUserDateManageTool::~FUserDateManageTool()
{

}

void FUserDateManageTool::setSqlLink(TSharedRef<FSimpleMysqlLink> Link_)
{
	//pDataBaseLinkName = Link_;

	/*if (pDataBaseLinkName)
	{
		UE_LOG(LogTemp, Log, TEXT("setSqlLink"));

		TMap<FString, FString> InsertDatas;

		FSimpleMysqlQueryParameters QueryParameters;

		FString ErrorMsg;

		FDateTime nowtime = FDateTime::Now();

		InsertDatas.Add("nickname", "Mrcaol");
		InsertDatas.Add("power", "normal");
		InsertDatas.Add("avatar", "NULL");
		InsertDatas.Add("register", nowtime.ToString());

		pDataBaseLinkName->InsertTableData(users_TableName, InsertDatas, QueryParameters, ErrorMsg);
	}*/
}

bool FUserDateManageTool::RegisterNewUser(FDMUserData OneUserData, FString Password, FString workID)
{
	if (!pDataBaseLinkName)
	{
		return false;
	}

	TMap<FString, FString> InsertDatas;

	FSimpleMysqlQueryParameters QueryParameters;

	FString ErrorMsg;

	FDateTime nowtime = FDateTime::Now();

	InsertDatas.Add("nickname", "imrcaoaa");
	InsertDatas.Add("power", "normal");
	InsertDatas.Add("avatar", "NULL");
	InsertDatas.Add("register", nowtime.ToString());

	if (pDataBaseLinkName->InsertTableData(users_TableName, InsertDatas, QueryParameters, ErrorMsg))
	{

		//pDataBaseLinkName->InsertTableData(user_land_TableName, );


		return true;
	}
	



	return false;
}

bool FUserDateManageTool::JudgeOnePhoneNumberExist(FString PhoneNumber)
{

	return false;
}

bool FUserDateManageTool::GetDataBasePassword(FString PhoneNumber, FString& Password)
{
	return false;
}

int FUserDateManageTool::GetUserLoggingStatus(FString PhoneNumber)
{

	return 0;
}

bool FUserDateManageTool::UpdateUserLoginStatus(FString workID, FString Identity, int& userID)
{
	return false;

}

bool FUserDateManageTool::GetOneUserBaseData(FDMUserData& OneUserData, int userid)
{
	return false;
}

bool FUserDateManageTool::UpdateUserLogoutStatus(int userID)
{
	return false;
}

bool FUserDateManageTool::UpdateUserLoginTIme(int userID)
{
	return false;

}

bool FUserDateManageTool::UpdateUserLoginTIme(FString Identify, int64& Time)
{
	return false;
}

FString FUserDateManageTool::GetCurrentUserPassword(int userID)
{
	FString ww = "d";

	return ww;
}

bool FUserDateManageTool::ModifyCurrentUserPassword(int userID, FString NewPassword)
{
	return false;
}

int FUserDateManageTool::GetUserIDWithIdentifier(FString Identifier)
{
	return 0;
}

FString FUserDateManageTool::uitoa(uint32 n)
{
	FString ss;

	return ss;
}
