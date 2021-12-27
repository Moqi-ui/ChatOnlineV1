
// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Hall.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CircularThrobber.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "Widgets/Input/SEditableTextBox.h"

#include "../Core/UI_CoreMacro.h"
#include "ThreadManage.h"
#include "../../MobyGameType.h"
#include <Kismet/GameplayStatics.h>

#include "UI_OneRoom.h"
#include "Gaming/ChatOnLine_GameInstance.h"


void UUI_Hall::NativeConstruct()
{
	Super::NativeConstruct();

	MenuButton->OnReleased.AddDynamic(this, &UUI_Hall::OpenMenuPage);
	QuitMenuButton->OnReleased.AddDynamic(this,&UUI_Hall::CloseMenuPage);
	RoomPage->OnReleased.AddDynamic(this, &UUI_Hall::SwitchCreateRoomPage);
	SerachRoom->OnReleased.AddDynamic(this, &UUI_Hall::SwiichSerachRoomPage);
	CreateRoomButton->OnReleased.AddDynamic(this, &UUI_Hall::TryCreateRoom);
	//JoinRoomButton->OnReleased.AddDynamic(this, &UUI_Hall::JoinCurrentSelectedRoom);
	FindRoomButton->OnReleased.AddDynamic(this, &UUI_Hall::SerachCurrentRoom);

	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, "NativeConstruct()");

	//InputRoomName = (SEditableTextBox*)GetWidgetFromName(TEXT("InputRoomName"));


	//循环绑定 指导成功为止
	BindClientRcv();
}

void UUI_Hall::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUI_Hall::BindClientRcv()
{
	if (ACharacterHall* InCharacterHall = GetCurrentPawn<ACharacterHall>())
	{
		if (InCharacterHall->GetClient())
		{
			InCharacterHall->GetClient()->GetController()->RecvDelegate.AddLambda([this](uint32 ProtocolNumber, FSimpleChannel* Channel)
				{
					this->RecvProtocol(ProtocolNumber, Channel);
				});
		}
		else
		{
			GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindClientRcv(); });
		}
	}
}



void UUI_Hall::LoginCallback()
{
	//openLevel
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("150.158.18.192:7777")));
	//UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("127.0.0.1")));

}

void UUI_Hall::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
		case SP_CreateRoomSuccess:
		{
			FString RoomInfo;
			FString Port;
			SIMPLE_PROTOCOLS_RECEIVE(SP_CreateRoomSuccess, RoomInfo);

			RoomInfo.Split("/", &Port,nullptr);

			FString URL = FString::Printf(TEXT("127.0.0.1:%s"),*Port);

			//知识点：FString To FName  :  FName TestName = *URL;
			UGameplayStatics::OpenLevel(GetWorld(), *URL);


			UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());
			if (Instance)
			{
				Instance->SetCurrentRoomInfo(RoomInfo);
				Instance->AddOnePlayerNumbers();
				int fff = Instance->GetCurrentPlayerNumbers();
				UE_LOG(LogTemp, Warning, TEXT("UE_LOG:SP_CreateRoomSuccess_RoomName:%s;PlayerNumber:%d"),*RoomInfo, fff);

			}

			LoginMsg(TEXT("Login failed~"));
			break;
		}
		case SP_FindRoom:
		{
			FString Result;

			SIMPLE_PROTOCOLS_RECEIVE(SP_FindRoom, Result);

			//FString LeftPort, RightName;

			//Result.Split("-", &LeftPort, &RightName);

			CreateRoomWidget(Result);

			break;
		}
	}
}

void UUI_Hall::LoginMsg(FString Mes)
{
	/*if (TipText)
	{
		TipText->SetText(FText::FromString(Mes));
	}*/
}

void UUI_Hall::OpenMenuPage()
{
	MenuPage->SetVisibility(ESlateVisibility::Visible);
	GEngine->AddOnScreenDebugMessage(-1,4,FColor::Blue, "OpenMenuPage()");
}
void UUI_Hall::CloseMenuPage()
{

	

	MenuPage->SetVisibility(ESlateVisibility::Hidden);
	GEngine->AddOnScreenDebugMessage(-1,4,FColor::Blue, "CloseMenuPage()");

}
void UUI_Hall::SwitchCreateRoomPage()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, "SwitchCreateRoomPage()");

}
void UUI_Hall::SwiichSerachRoomPage()
{

	//SEND_DATA_Hall(SP_FindRoom)
	MenuSwitcher->SetActiveWidgetIndex(1);
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, "SwiichSerachRoomPage()");

}
void UUI_Hall::TryCreateRoom()
{
	//FString RoomID = "9999";
	FString RoomNameInfo = UserRoomName.ToString();

	//RoomName = UserInputRoomName->GetText().ToString();

	SEND_DATA_Hall(SP_CreateRoom, RoomNameInfo)

	
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, RoomNameInfo);

}
void UUI_Hall::SerachCurrentRoom()
{
	FString EmptyStr = "Empty";

	SEND_DATA_Hall(SP_FindRoom, EmptyStr);

	//CreateRoomWidget();
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, "SerachCurrentRoom()");

}
void UUI_Hall::JoinCurrentSelectedRoom(FString RoomPort)
{
	//FString Port = "9998";

	FString URL = FString::Printf(TEXT("127.0.0.1:%s"), *RoomPort);

	//知识点：FString To FName  :  FName TestName = *URL;
	UGameplayStatics::OpenLevel(GetWorld(), *URL);

	UChatOnLine_GameInstance* Instance = Cast<UChatOnLine_GameInstance>(GetGameInstance());
	if (Instance)
	{
		//Instance->SetCurrentRoomInfo(RoomInfo);
		Instance->AddOnePlayerNumbers();
		int dddd = Instance->GetCurrentPlayerNumbers();
		UE_LOG(LogTemp, Warning, TEXT("UE_LOG:JoinCurrentSelectedRoom:%d"), dddd);

	}

	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, "JoinCurrentSelectedRoom()");

}

void UUI_Hall::CreateRoomWidget(FString ServerNameInfo)
{
	ServerRooms.Empty();

	AnalysisString(ServerNameInfo);

	ScrollRoomList->ClearChildren();

	for (auto& Elem : ServerRooms)
	{
		UUI_OneRoom* OneRoom = nullptr;

		TSubclassOf<UUI_OneRoom> WidgetClass = LoadClass<UUI_OneRoom>(this, TEXT("/Game/ChatOnline/WFY_Widget/Hall/UI_RoomButton.UI_RoomButton_C"));

		if (WidgetClass)
		{
			OneRoom = CreateWidget<UUI_OneRoom>(GetWorld(), WidgetClass);

			OneRoom->JoinRoom.BindUObject(this, &UUI_Hall::JoinCurrentSelectedRoom);

			OneRoom->SetRoomInfo(Elem);
		}

		ScrollRoomList->AddChild(OneRoom);
	}


}

void UUI_Hall::AnalysisString(FString Str)
{
	//ServerRooms.Empty();

	FString LeftStr;

	if (!Str.IsEmpty())
	{
		if (Str.Contains("-"))
		{
			Str.Split("-", &LeftStr, &Str);
			ServerRooms.Add(LeftStr);
			AnalysisString(Str);
		}
		else
		{
			ServerRooms.Add(Str);
		}
	}
}
void UUI_Hall::SetInputRoomName(FText tt)
{
	///FText te = FText::FromString("fd");
	UserRoomName = tt;
	
}
