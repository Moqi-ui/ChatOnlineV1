// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

/**
 * 
 */
//UCLASS()
//class CHATONLINE_WFY_API UUI_Base : public UUserWidget
//{
//	GENERATED_BODY()
//	
//};


class UWidgetAnimation;
class UUI_Tip;
UCLASS()
class CHATONLINE_WFY_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

		//Ã· æ¿‡
		UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_Tip> TipClass;

public:
	UUI_Base(const FObjectInitializer& ObjectInitializer);

	UWidgetAnimation* GetNameWidgetAnimation(const FString& WidgetAnimationName) const;

	//AMobyGameHUD* GetHUD();

	//AMobyGamePlayerState* GetPlayerState();
	//AMobyGameState* GetGameState();

	FORCEINLINE int64 GetPlayerID() { return PlayerID; }
	//void SetPlayerID(int64 InPlayerID);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Tip)
		virtual UWidget* GetTip();

protected:
	UPROPERTY()
		int64 PlayerID;

	UPROPERTY()
		UUI_Tip* TipPtr;

};
