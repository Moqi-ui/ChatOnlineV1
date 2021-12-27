// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ChatOnLine_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API UChatOnLine_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	



public:

	virtual void Init() override;



public:


	//FORCEINLINE int GetCurrentPlayerNumbers() { return Inst_CurrentPlayerNumbers; };
	int GetCurrentPlayerNumbers() { return Inst_CurrentPlayerNumbers; };

	void AddOnePlayerNumbers();

	void ReduceOnePlayerNumbers();

	void SetCurrentRoomInfo(FString Key_RoomInfo);

	FString GetCurrentRoomInfo() { return Key_CurrentRoomInfo; };

private:

	int Inst_CurrentPlayerNumbers;

	FString Key_CurrentRoomInfo;
};
