// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Tickable.h"
//#include "BaseVoiceControlSystem.h"
#include "ChatOnLine_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API UChatOnLine_GameInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()
	



public:

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;

	virtual void Shutdown() override;

public:


	//FORCEINLINE int GetCurrentPlayerNumbers() { return Inst_CurrentPlayerNumbers; };
	int GetCurrentPlayerNumbers() { return Inst_CurrentPlayerNumbers; };

	void AddOnePlayerNumbers();

	void ReduceOnePlayerNumbers();

	void SetCurrentRoomInfo(FString Key_RoomInfo);

	FString GetRoomID() { return RoomID; };

	FString GetUserID() { return UserID; };

	FString GetCurrentRoomInfo() { return Key_CurrentRoomInfo; };

	//UBaseVoiceControlSystem* GetVoiceControlSystem() { return VoiceControlSystem; };

protected:

	//UBaseVoiceControlSystem* VoiceControlSystem;

	//ITMGContext* TMGContent1;

private:

	int Inst_CurrentPlayerNumbers;

	FString Key_CurrentRoomInfo;

	FString RoomID;

	FString UserID;
};