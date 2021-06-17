#include "UserDataManagerTool.h"



FUserDataManagerTool::FUserDataManagerTool()
{
	//UE_LOG(LogTemp, Log, TEXT("2222FUserDataManagerTool()"));
}

FUserDataManagerTool::~FUserDataManagerTool()
{

}

void FUserDataManagerTool::setSqlLink(TSharedPtr<FSimpleMysqlLink> Link_)
{
	pDataBaseLinkName = Link_;

	if (pDataBaseLinkName)
	{
		UE_LOG(LogTemp, Log, TEXT("setSqlLink"));
	}
}

bool FUserDataManagerTool::RegisterNewUser(FDMUserData OneUserData, FString Password, FString workID)
{
	if (!pDataBaseLinkName)
	{
		return false;
	}


	//pDataBaseLinkName->InsertTableData();



	return false;
}

bool FUserDataManagerTool::JudgeOnePhoneNumberExist(FString PhoneNumber)
{

	return false;
}

bool FUserDataManagerTool::GetDataBasePassword(FString PhoneNumber, FString& Password)
{
	return false;
}

int FUserDataManagerTool::GetUserLoggingStatus(FString PhoneNumber)
{

	return 0;
}

bool FUserDataManagerTool::UpdateUserLoginStatus(FString workID, FString Identity, int& userID)
{
	return false;

}

bool FUserDataManagerTool::GetOneUserBaseData(FDMUserData& OneUserData, int userid)
{
	return false;
}

bool FUserDataManagerTool::UpdateUserLogoutStatus(int userID)
{
	return false;
}

bool FUserDataManagerTool::UpdateUserLoginTIme(int userID)
{
	return false;

}

bool FUserDataManagerTool::UpdateUserLoginTIme(FString Identify, int64& Time)
{
	return false;
}

FString FUserDataManagerTool::GetCurrentUserPassword(int userID)
{
	FString ww = "d";

	return ww;
}

bool FUserDataManagerTool::ModifyCurrentUserPassword(int userID, FString NewPassword)
{
	return false;
}

int FUserDataManagerTool::GetUserIDWithIdentifier(FString Identifier)
{
	return 0;
}

FString FUserDataManagerTool::uitoa(uint32 n)
{
	FString ss;

	return ss;
}
