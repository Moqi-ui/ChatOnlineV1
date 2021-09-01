// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleController.h"
#include "ClientObjectController.generated.h"

UCLASS()
class UClientObjectController :public USimpleController
{
	GENERATED_BODY()

public:

protected:
	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Close();
	virtual void RecvProtocol(uint32 InProtocol);
};