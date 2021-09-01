// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGmeMode.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API ALoginGmeMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoginGmeMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
