// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginRegisterInterface.h"
#include "Engine.h"

void ULoginRegisterInterface::PostInitProperties()
{
	Super::PostInitProperties();


}

void ULoginRegisterInterface::Print_F(FString InputStr)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, InputStr);
}

void ULoginRegisterInterface::init()
{
	userLandManger = FUserLandManager::Get();
}

void ULoginRegisterInterface::ShowOrCreateOneWidget(UWidget* SelfWidget, TSubclassOf<UUserWidget> MyUserWidget)
{

}