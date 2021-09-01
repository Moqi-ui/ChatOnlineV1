// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "UI/Core/UI_CoreBase.h"
//#include "UI_LoginMain.generated.h"
//
///**
// * 
// */
//UCLASS()
//class CHATONLINE_WFY_API UUI_LoginMain : public UUI_CoreBase
//{
//	GENERATED_BODY()
//	
//};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_CoreBase.h"
#include "UI_LoginMain.generated.h"

UCLASS()
class UUI_LoginMain : public UUI_CoreBase
{
	GENERATED_BODY()

		UPROPERTY(meta = (BindWidget))
		class UUI_Login* UI_Login;

	/*UPROPERTY(meta = (BindWidget))
	class UUI_Register *UI_Register;

	UPROPERTY(meta = (BindWidget))
	class UUI_ServerIn *UI_ServerIn;*/

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	void OpenMainUI();
	void CloseMainUI();

	void OpenLoginUI();
	void CloseLoginUI();

	void OpenRegisterUI();
	void CloseRegisterUI();

	void OpenServerUI();
	void CloseServerUI();

	void OpenServerList();
	void CloseServerList();

	UFUNCTION()
		void MainOutAnimationFinish();

	UFUNCTION()
		void LoginOutAnimationFinish();

	//void AddSeverList(uint8 InType, const TArray<struct FGateInfo>& InNetInfo);
};

