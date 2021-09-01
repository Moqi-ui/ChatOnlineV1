// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LoginPawn.generated.h"

//UCLASS()
//class CHATONLINE_WFY_API ALoginPawn : public APawn
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this pawn's properties
//	ALoginPawn();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//};

class FSimpleNetManage;
UCLASS()
class CHATONLINE_WFY_API ALoginPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALoginPawn();

	FSimpleNetManage* GetClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game end 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	FSimpleNetManage* Client;

};
