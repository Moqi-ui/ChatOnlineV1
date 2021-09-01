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
* @author			RenZhai						(��լ)
* @date				2018, 09, 28, 10:30: 00		(2018��09��28��10:30 : 00)
* @brief			Landing UI					(��½UI����)
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

		//�˺�����ʵ��
		//account input instance
		UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Account;

	//��������ʵ��
	//password input instance
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* Password;

	//������Ϸ
	// login game
	UPROPERTY(meta = (BindWidget))
		class UButton* SignInButton;

	//����ע��ʵ��
	// simple registration instance
	UPROPERTY(meta = (BindWidget))
		class UButton* SignUpButton;

	//��ʾ Game
	// hint Game
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TipText;

	//��½��Ϣ
	// landing information
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LoginMes;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	//��鱾�ؿͻ����˻������Ƿ�������
	// check whether local client account input is meaningful.
	bool IsAccountValid();

	//��鱾�ؿͻ������������Ƿ�������
	// check whether the local client password entry is meaningful.
	bool IsPasswordValid();

	//������Ϸ
	// login game
	UFUNCTION()
		void SignInGame();

	//ע��
	//register
	UFUNCTION()
		void SignUpGame();

	//��ʾ������Ϣ
	//@Mes		��ʾ����
	//prompt error message
	//@Mes prompt content
	void LoginMsg(FString Mes);

	void LoginCallback();

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);
};

