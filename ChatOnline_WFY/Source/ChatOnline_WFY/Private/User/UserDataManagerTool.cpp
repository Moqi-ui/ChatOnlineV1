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