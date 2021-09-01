#pragma once
#include "../../Login/LoginPawn.h"
#include "../../Protocols/LoginProtocols.h"
#include "SimpleNetManage.h"
#include "UObject/SimpleController.h"

#define SEND_DATA(InProtocols,...) \
if (ALoginPawn* InPawn = GetCurrentPawn<ALoginPawn>()) \
{ \
	SIMPLE_CLIENT_SEND(InPawn->GetClient(),InProtocols,__VA_ARGS__);\
}