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
#include "UI_Register.generated.h"

class UUI_LoginMain;

UCLASS()
class UUI_Register : public UUI_CoreBase
{
	GENERATED_BODY()
	
	//�û���
	//anonymous instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *UserName;

	//�˻�ʵ��
	//account instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UserPhone;
	
	//����ʵ��
	//password instance
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UserPassword;

	//��֤������
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* VerificationCode;

	//��ȡ��֤��GetVCodeBuuton
	UPROPERTY(meta = (BindWidget))
	class UButton *GetVCodeBuuton;

	//����ע�ᰴť
	//Sending button information completed by registration
	UPROPERTY(meta = (BindWidget))
	class UButton *RegisterButton;

	//���ص���½����İ�ť
	//Return to the landing interface button
	UPROPERTY(meta = (BindWidget))
	class UButton *ReturnMainPage;

	//ע�����Ϣ
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

	//�����ҵ�����
	// random player's name
	UFUNCTION()
	void RandPlayerName();

	UFUNCTION()
	void SendPlayerRegisterToServer();

	UFUNCTION()
	void TurnOffRegisterUI();

	//���Է�����֤��
	UFUNCTION()
	void TrySendVerification();

	//�ڷ���˼�������Ƿ���ȷ
	bool CheckNameToServer();

	void BindClientRcv();

	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	//������֤���Ƿ�������ȷ
	bool VerifyVerification();

	bool VerifyInputPhone(FString Phone);


	//��������Ϣ
	//Set new message
	void SetNewMess(const FString& NewMess);


private:

	FString SendUserVerification;
};
