// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @author			Imrcao						(����)
* @date				2021��11��11, 11:32: 00		(2018��09��28��10:30 : 00)
* @brief			Register UI					(ע��UI����)
* @see
* @See				http://www.imrcao.com
* @note
**********************************************************/

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_CoreBase.h"
#include "UI_LoginMain.generated.h"


class UUI_Login;
class UUI_Register;

UCLASS()
class UUI_LoginMain : public UUI_CoreBase
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UUI_Login* UI_Login;

	UPROPERTY(meta = (BindWidget))
	class UUI_Register *UI_Register;

	/*UPROPERTY(meta = (BindWidget))
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

