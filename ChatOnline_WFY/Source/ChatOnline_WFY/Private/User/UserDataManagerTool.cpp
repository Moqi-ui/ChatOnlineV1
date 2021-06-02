#include "UserDataManagerTool.h"



FUserDataManagerTool::FUserDataManagerTool()
{
	UE_LOG(LogTemp, Log, TEXT("2222FUserDataManagerTool()"));
}

FUserDataManagerTool::~FUserDataManagerTool()
{

}

void FUserDataManagerTool::setSqlLink(TSharedPtr<FSimpleMysqlLink> Link_)
{
	Link = Link_;

	if (Link)
	{
		UE_LOG(LogTemp, Log, TEXT("setSqlLink"));
	}
}