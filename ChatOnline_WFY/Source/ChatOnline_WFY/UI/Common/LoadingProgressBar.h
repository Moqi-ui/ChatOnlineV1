// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Tickable.h"
#include "LoadingProgressBar.generated.h"


UCLASS()
class CHATONLINE_WFY_API ULoadingProgressBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidegt))
		class UProgressBar* LoadingBar;

	UPROPERTY(meta = (BindWidget))
		class UTextblock* PercentText;


public:

	//void Tick(FGeometry MyGeometry, float InDeltaTime);

	//virtual void Tick(float DeltaTime) override;

	//virtual bool IsTickable() const override;

	//virtual TStatId GetStatId() const override;

	void SetTextTitle(FString text);

};
