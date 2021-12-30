
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_OneRoom.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CircularThrobber.h"
#include "Components/WidgetSwitcher.h"

void UUI_OneRoom::NativeConstruct()
{
	Super::NativeConstruct();


	JoinRoomButto->OnReleased.AddDynamic(this, &UUI_OneRoom::OnClickJoinRoomButton);

	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, "NativeConstruct()");


}

void UUI_OneRoom::NativeDestruct()
{
	Super::NativeDestruct();
}


void UUI_OneRoom::OnClickJoinRoomButton()
{
	//DE_JoinRoom.Excute();

	JoinRoom.ExecuteIfBound(HandleRoomInfo);
}

void UUI_OneRoom::SetRoomInfo(FString ServerRoomInfo)
{
	HandleRoomInfo = ServerRoomInfo;

	ServerRoomInfo.Split("/", &RoomPort, &RoomName);
	RoomID = RoomName;
	RoomID.Split("/", &RoomName, &RoomID);

	FString ShowInfo = FString::Printf(TEXT("RoomName:%s--RoomID:%s--Port:%s"), *RoomName, *RoomID, *RoomPort);

	FText text = FText::FromString(ShowInfo);

	RoomInfo->SetText(text);
}





