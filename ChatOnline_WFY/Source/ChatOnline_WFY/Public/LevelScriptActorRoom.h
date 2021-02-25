// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelScriptActorRoom.generated.h"

class UVoiceControlSystem;
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

private:

	UVoiceControlSystem* myVoiceControlSystem;

};
