// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************
*
* @author			RenZhai						(��լ)
* @date				2018, 09, 28, 10:30: 00		(2018��09��28��10:30 : 00)
* @brief			Register UI					(ע��UI����)
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
	
	//����ʵ��
	//anonymous instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *NickName;

	//�˻�ʵ��
	//account instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *Account;
	
	//����ʵ��
	//password instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *Password;

	//������ְ�ť
	//random name button
	UPROPERTY(meta = (BindWidget))
	class UButton *RandNameButton;

	//����ע����ɵİ�ť��Ϣ
	//Sending button information completed by registration
	UPROPERTY(meta = (BindWidget))
	class UButton *SendButton;

	//���ص���½����İ�ť
	//Return to the landing interface button
	UPROPERTY(meta = (BindWidget))
	class UButton *TurnOffButton;

	//ע�����Ϣ
	//Registration message
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *Messl;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//�����ҵ�����
	// random player's name
	UFUNCTION()
	void RandPlayerName();

	UFUNCTION()
	void SendPlayerRegisterToServer();

	//�ڷ���˼�������Ƿ���ȷ
	bool CheckNameToServer();

	void BindClientRcv();

	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	//�ر�ע��UI
	//close registration UI
	UFUNCTION()
	void TurnOffRegisterUI();

	//��������Ϣ
	//Set new message
	void SetNewMess(const FString& NewMess);
};
