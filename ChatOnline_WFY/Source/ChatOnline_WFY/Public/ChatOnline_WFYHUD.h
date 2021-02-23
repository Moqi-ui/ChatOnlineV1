// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ChatOnline_WFYHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API AChatOnline_WFYHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category = "WFY_UserWidget")
		TSubclassOf<class UWFY_MainPage> WidgetClass;
	
};
