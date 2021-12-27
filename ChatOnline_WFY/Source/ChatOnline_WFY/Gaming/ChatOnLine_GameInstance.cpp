// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatOnLine_GameInstance.h"



void UChatOnLine_GameInstance::Init()
{
	Super::Init();

	Inst_CurrentPlayerNumbers = 0;
}
void UChatOnLine_GameInstance::AddOnePlayerNumbers()
{
	Inst_CurrentPlayerNumbers++;
}

void UChatOnLine_GameInstance::ReduceOnePlayerNumbers()
{
	Inst_CurrentPlayerNumbers--;
}

void UChatOnLine_GameInstance::SetCurrentRoomInfo(FString Key_RoomInfo)
{
	Key_CurrentRoomInfo = Key_RoomInfo;
}