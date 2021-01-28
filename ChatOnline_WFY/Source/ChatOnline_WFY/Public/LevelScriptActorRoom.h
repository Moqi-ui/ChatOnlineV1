// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "auth_buffer.h"
#include "tmg_sdk.h"
#include "VoiceControlSystem.h"
#include "LevelScriptActorRoom.generated.h"

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API ALevelScriptActorRoom : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ALevelScriptActorRoom();
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	void onChangeDemo();
	void CopyAllAssetsToExternal();

#if PLATFORM_PS4 || PLATFORM_XBOXONE
	void OnKeyUp();
	void OnKeyDown();
	void OnKeyRight();
	void OnKeyLeft();
	void OnKeyEnter();
	void OnKeyEnterRelease();
#endif

private:
	UPROPERTY()
		UBaseVoiceControlSystem* m_pTestDemoViewController;
	UPROPERTY()
		UBaseVoiceControlSystem* m_pExperientialDemoViewController;
	UPROPERTY()
		UBaseVoiceControlSystem* m_pCurrentViewController;
};
