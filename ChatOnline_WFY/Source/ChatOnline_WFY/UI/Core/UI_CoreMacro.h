#pragma once
#include "../../Login/LoginPawn.h"
#include "../../Hall/CharacterHall.h"
#include "../../ChatOnline_WFYCharacter.h"
#include "Protocols/LoginProtocols.h"
#include "SimpleNetManage.h"
#include "UObject/SimpleController.h"

#define SEND_DATA(InProtocols,...) \
if (ALoginPawn* InPawn = GetCurrentPawn<ALoginPawn>()) \
{ \
	SIMPLE_CLIENT_SEND(InPawn->GetClient(),InProtocols,__VA_ARGS__);\
}

#define SEND_DATA_Hall(InProtocols,...) \
if (ACharacterHall* InCharacterHall = GetCurrentPawn<ACharacterHall>()) \
{ \
	SIMPLE_CLIENT_SEND(InCharacterHall->GetClient(),InProtocols,__VA_ARGS__);\
}

#define SEND_DATA_GAME(InProtocols,...) \
if (AChatOnline_WFYCharacter* InCharacterGame = GetCurrentPawn<AChatOnline_WFYCharacter>()) \
{ \
	SIMPLE_CLIENT_SEND(InCharacterGame->GetClient(),InProtocols,__VA_ARGS__);\
}