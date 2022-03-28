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
#include "UI_Register.generated.h"

class UUI_LoginMain;

UCLASS()
class UUI_Register : public UUI_CoreBase
{
	GENERATED_BODY()
	
	//用户名
	//anonymous instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *UserName;

	//账户实例
	//account instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UserPhone;
	
	//密码实例
	//password instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UserPassword;

	//验证码正文
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* VerificationCode;

	//获取验证码GetVCodeBuuton
	UPROPERTY(meta = (BindWidget))
	class UButton *GetVCodeBuuton;

	//尝试注册按钮
	//Sending button information completed by registration
	UPROPERTY(meta = (BindWidget))
	class UButton *RegisterButton;

	//返回到登陆界面的按钮
	//Return to the landing interface button
	UPROPERTY(meta = (BindWidget))
	class UButton *ReturnMainPage;

	//注册的消息
	//Registration message
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *Prompt;

	UPROPERTY(meta = (BindWidget))
	class UButton* LoginIn;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* countDown;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//随机玩家的名字
	// random player's name
	UFUNCTION()
	void RandPlayerName();

	UFUNCTION()
	void SendPlayerRegisterToServer();

	UFUNCTION()
	void TurnOffRegisterUI();

	//尝试发送验证码
	UFUNCTION()
	void TrySendVerification();

	//在服务端检测名字是否正确
	bool CheckNameToServer();

	void BindClientRcv();

	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	//核验验证码是否输入正确
	bool VerifyVerification();

	bool VerifyInputPhone(FString Phone);


	//设置新消息
	//Set new message
	void SetNewMess(const FString& NewMess);


private:

	FString SendUserVerification;
};
