// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "COL_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API UCOL_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UCOL_SaveGame();

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerAccount;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerPassword;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        bool bIsRemberMe = false;
    
};
