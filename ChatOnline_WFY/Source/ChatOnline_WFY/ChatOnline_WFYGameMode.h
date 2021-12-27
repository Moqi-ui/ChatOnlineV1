// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChatOnline_WFYGameMode.generated.h"


UCLASS(minimalapi)
class AChatOnline_WFYGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChatOnline_WFYGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;




public:

	//int MaxPlayerNum = 0;

	//int CurrentPlayerNum = 0;

};



