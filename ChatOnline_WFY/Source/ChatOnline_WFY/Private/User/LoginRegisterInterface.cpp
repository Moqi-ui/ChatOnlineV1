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

bool ULoginRegisterInterface::QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug)
{

	Link->QueryLinkResult(SQL, Results, ErrMesg, SaveType, Debug);

	return false;
}
