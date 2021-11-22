// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @author			Imrcao						(曹洛)
* @date				2021，11，11, 11:32: 00		(2018年09月28日10:30 : 00)
* @brief			Register UI					(注册UI界面)
* @see
* @See				http://www.imrcao.com
* @note
**********************************************************/
#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_CoreBase.h"
#include "UI_Login.generated.h"

class UUI_LoginMain;

UCLASS()
class UUI_Login : public UUI_CoreBase
{
	GENERATED_BODY()

	//账号输入实例
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Account;

	//密码输入实例
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Password;

	//登入游戏
	UPROPERTY(meta = (BindWidget))
		class UButton* SignInButton;

	//简易注册实例
	UPROPERTY(meta = (BindWidget))
		class UButton* SignUpButton;

	//提示 Game
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TipText;

	//登陆信息
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LoginMes;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//检查本地客户端账户输入是否有意义
	bool IsAccountValid();

	//检查本地客户端密码输入是否有意义
	bool IsPasswordValid();

	//登入游戏
	UFUNCTION()
	void SignInGame();

	//注册
	UFUNCTION()
	void SignUpGame();

	//提示错误信息
	void LoginMsg(FString Mes);

	void LoginCallback();

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);
};

