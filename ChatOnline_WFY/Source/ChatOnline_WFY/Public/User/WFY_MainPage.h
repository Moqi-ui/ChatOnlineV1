// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WFY_MainPage.generated.h"

class UVoiceControlSystem;

/**
 * 
 */
UCLASS()
class CHATONLINE_WFY_API UWFY_MainPage : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	UWFY_MainPage* GetInitLoadPage();

public:

	/**Get or create VoiceController		by Mr.cao 20210226*/
	UFUNCTION(BlueprintCallable, Category = "GME_Voice")
	UVoiceControlSystem* GetOrCreateVoiceController();

	/**���Ե�½��Ϸ(TryLoginTheGame)			by Mr.cao 20210223*/
	UFUNCTION(BlueprintCallable, Category = "LoginPage")
		bool TryLoginGame();

	/**���ע�ᰴť-Click register button		by Mr.cao 20210223*/
	UFUNCTION(BlueprintCallable, Category = "LoginPage")
		void ClickRegisterButton();

	/*��������-Forget the password			by Mr.cao 20210223**/
	UFUNCTION(BlueprintCallable, Category = "LoginPage")
		void ClickForgetPassword();
private:

	/**��ʼ����ҳ��				by Mr.cao 20210223*/
	UWFY_MainPage* iniLoadPage;
	
	/**��½ҳ��					by Mr.cao 20210223*/
	UWFY_MainPage* LoginPage;

	/**ע��ҳ��					by Mr.cao 20210223*/
	UWFY_MainPage* RegisterPage;


private:

	UVoiceControlSystem* VoiceController;
	
};
