// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChatOnline_WFYGameMode.h"
#include "ChatOnline_WFYCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChatOnline_WFYGameMode::AChatOnline_WFYGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
