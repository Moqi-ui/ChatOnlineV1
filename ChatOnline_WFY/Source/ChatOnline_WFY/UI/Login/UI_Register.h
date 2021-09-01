// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @author			RenZhai						(人宅)
* @date				2018, 09, 28, 10:30: 00		(2018年09月28日10:30 : 00)
* @brief			Register UI					(注册UI界面)
* @see
* @tutorial See		http://www.aboutcg.org/course/tut_ue4programming_180119/
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
	
	//匿名实例
	//anonymous instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *NickName;

	//账户实例
	//account instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *Account;
	
	//密码实例
	//password instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *Password;

	//随机名字按钮
	//random name button
	UPROPERTY(meta = (BindWidget))
	class UButton *RandNameButton;

	//发送注册完成的按钮信息
	//Sending button information completed by registration
	UPROPERTY(meta = (BindWidget))
	class UButton *SendButton;

	//返回到登陆界面的按钮
	//Return to the landing interface button
	UPROPERTY(meta = (BindWidget))
	class UButton *TurnOffButton;

	//注册的消息
	//Registration message
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *Messl;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//随机玩家的名字
	// random player's name
	UFUNCTION()
	void RandPlayerName();

	UFUNCTION()
	void SendPlayerRegisterToServer();

	//在服务端检测名字是否正确
	bool CheckNameToServer();

	void BindClientRcv();

	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	//关闭注册UI
	//close registration UI
	UFUNCTION()
	void TurnOffRegisterUI();

	//设置新消息
	//Set new message
	void SetNewMess(const FString& NewMess);
};
