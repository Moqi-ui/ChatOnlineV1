// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "UI/Core/UI_CoreBase.h"
//#include "UI_Login.generated.h"
//
///**
// * 
// */
//UCLASS()
//class CHATONLINE_WFY_API UUI_Login : public UUI_CoreBase
//{
//	GENERATED_BODY()
//	
//};

// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @author			RenZhai						(人宅)
* @date				2018, 09, 28, 10:30: 00		(2018年09月28日10:30 : 00)
* @brief			Landing UI					(登陆UI界面)
* @see
* @tutorial See		http://www.aboutcg.org/course/tut_ue4programming_180119/
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
		//account input instance
		UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Account;

	//密码输入实例
	//password input instance
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Password;

	//登入游戏
	// login game
	UPROPERTY(meta = (BindWidget))
		class UButton* SignInButton;

	//简易注册实例
	// simple registration instance
	UPROPERTY(meta = (BindWidget))
		class UButton* SignUpButton;

	//提示 Game
	// hint Game
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TipText;

	//登陆信息
	// landing information
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LoginMes;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//检查本地客户端账户输入是否有意义
	// check whether local client account input is meaningful.
	bool IsAccountValid();

	//检查本地客户端密码输入是否有意义
	// check whether the local client password entry is meaningful.
	bool IsPasswordValid();

	//登入游戏
	// login game
	UFUNCTION()
		void SignInGame();

	//注册
	//register
	UFUNCTION()
		void SignUpGame();

	//提示错误信息
	//@Mes		提示内容
	//prompt error message
	//@Mes prompt content
	void LoginMsg(FString Mes);

	void LoginCallback();

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);
};

