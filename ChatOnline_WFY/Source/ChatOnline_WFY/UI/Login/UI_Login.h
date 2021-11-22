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
#include "UI_Login.generated.h"

class UUI_LoginMain;

UCLASS()
class UUI_Login : public UUI_CoreBase
{
	GENERATED_BODY()

	//�˺�����ʵ��
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Account;

	//��������ʵ��
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Password;

	//������Ϸ
	UPROPERTY(meta = (BindWidget))
		class UButton* SignInButton;

	//����ע��ʵ��
	UPROPERTY(meta = (BindWidget))
		class UButton* SignUpButton;

	//��ʾ Game
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TipText;

	//��½��Ϣ
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LoginMes;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//��鱾�ؿͻ����˻������Ƿ�������
	bool IsAccountValid();

	//��鱾�ؿͻ������������Ƿ�������
	bool IsPasswordValid();

	//������Ϸ
	UFUNCTION()
	void SignInGame();

	//ע��
	UFUNCTION()
	void SignUpGame();

	//��ʾ������Ϣ
	void LoginMsg(FString Mes);

	void LoginCallback();

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);
};

