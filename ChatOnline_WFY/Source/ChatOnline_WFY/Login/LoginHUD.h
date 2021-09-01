// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoginHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API ALoginHUD : public AHUD
{
	GENERATED_BODY()

public:

	ALoginHUD();

	virtual void BeginPlay() override;
	
};
