// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeHall.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API AGameModeHall : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AGameModeHall();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
};
