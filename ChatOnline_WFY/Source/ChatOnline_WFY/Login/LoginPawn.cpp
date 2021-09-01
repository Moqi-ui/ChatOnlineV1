// Fill out your copyright notice in the Description page of Project Settings.

//
//#include "LoginPawn.h"
//
//// Sets default values
//ALoginPawn::ALoginPawn()
//{
// 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}
//
//// Called when the game starts or when spawned
//void ALoginPawn::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ALoginPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void ALoginPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginPawn.h"
#include "ThreadManage.h"
#include "Global/SimpleNetGlobalInfo.h"
#include "../Network/ClientObjectController.h"
#include "SimpleNetManage.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif
ALoginPawn::ALoginPawn()
{
	Client = NULL;
}

FSimpleNetManage* ALoginPawn::GetClient()
{
	return Client;
}

void ALoginPawn::BeginPlay()
{
	Super::BeginPlay();

	//2.初始化配置表
	FSimpleNetGlobalInfo::Get()->Init();//初始化我们通道

	//3.创建对象
	Client = FSimpleNetManage::CreateManage(ESimpleNetLinkState::LINKSTATE_CONNET, ESimpleSocketType::SIMPLESOCKETTYPE_UDP);
	FSimpleChannel::SimpleControllerDelegate.BindLambda(
		[]()->UClass*
		{
			return UClientObjectController::StaticClass();
		});

	//4.初始化
	if (!Client->Init())
	{
		Client = NULL;
		//UE_LOG(LogDBServer, Error, TEXT("Server Init fail."));
		return;
	}
}

void ALoginPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FSimpleNetManage::Destroy(Client);
	GThread::Get()->Destroy();
}

void ALoginPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GThread::Get()->Tick(DeltaTime);
	Client->Tick(DeltaTime);
}

void ALoginPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif



