// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChatOnline_WFYGameMode.h"
#include "ChatOnline_WFYCharacter.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Gaming/ChatOnLine_GameInstance.h"

AChatOnline_WFYGameMode::AChatOnline_WFYGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AChatOnline_WFYCharacter> PlayerPawnBPClass(TEXT("/Game/ChatOnline/WFY_Blueprint/Core/WFY_Character"));
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/ChatOnline/WFY_Blueprint/Core/ChatOnline_WFYHUD_BP"));

	//DefaultPawnClass = AChatOnline_WFYCharacter::StaticClass();
	if (PlayerPawnBPClass.Class!=NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	if (PlayerHUDBPClass.Class!=NULL)
	{
		HUDClass = PlayerHUDBPClass.Class;
	}

}


void AChatOnline_WFYGameMode::BeginPlay()
{
	Super::BeginPlay();



}

void AChatOnline_WFYGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChatOnline_WFYGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//CurrentPlayerNum++;

	UE_LOG(LogTemp, Warning, TEXT("UE_LOG:AChatOnline_WFYGameMode::PostLogin"));
	//UE_LOG(LogTemp, Warning, TEXT("Join_CurrentPlayerNum: %d"), CurrentPlayerNum);

	//UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());
	/*if (Instance)
	{
		Instance->AddOnePlayerNumbers();

		UE_LOG(LogTemp, Warning, TEXT("PostLogin_UChatOnLine_GameInstance: %d"), Instance->GetCurrentPlayerNumbers());
	}*/

}

void AChatOnline_WFYGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	//CurrentPlayerNum--;

	UE_LOG(LogTemp, Warning, TEXT("UE_LOG:AChatOnline_WFYGameMode::Logout"));

	/*UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());
	if (Instance)
	{
		Instance->ReduceOnePlayerNumbers();

		UE_LOG(LogTemp, Warning, TEXT("Logout_UChatOnLine_GameInstance: %d"), Instance->GetCurrentPlayerNumbers());
	}*/
}
