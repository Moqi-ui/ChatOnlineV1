// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeHall.h"
#include "CharacterHall.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

AGameModeHall::AGameModeHall()
{

	struct ConstructorHelpers::FClassFinder<ACharacter> CharacterHall (TEXT("/Game/ChatOnline/WFY_Blueprint/Hall/BP_CharacterHall"));

	if (CharacterHall.Class != NULL)
	{
		DefaultPawnClass = CharacterHall.Class;
	}
	else
	{
		DefaultPawnClass = ACharacterHall::StaticClass();
	}
}

void AGameModeHall::BeginPlay()
{
	Super::BeginPlay();



}

void AGameModeHall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameModeHall::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);


	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "PostLogin");
}

void AGameModeHall::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "PostLogin");

}