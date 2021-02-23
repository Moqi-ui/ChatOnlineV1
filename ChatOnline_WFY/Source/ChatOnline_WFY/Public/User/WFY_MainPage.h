// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WFY_MainPage.generated.h"

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

	/**³¢ÊÔµÇÂ½ÓÎÏ·(TryLoginTheGame)			by Mr.cao 20210223*/
	UFUNCTION(BlueprintCallable, Category = "LoginPage")
		bool TryLoginGame();

	/**µã»÷×¢²á°´Å¥-Click register button		by Mr.cao 20210223*/
	UFUNCTION(BlueprintCallable, Category = "LoginPage")
		void ClickRegisterButton();

	/*Íü¼ÇÃÜÂë-Forget the password			by Mr.cao 20210223**/
	UFUNCTION(BlueprintCallable, Category = "LoginPage")
		void ClickForgetPassword();
private:

	/**³õÊ¼¼ÓÔØÒ³Ãæ				by Mr.cao 20210223*/
	UWFY_MainPage* iniLoadPage;
	
	/**µÇÂ½Ò³Ãæ					by Mr.cao 20210223*/
	UWFY_MainPage* LoginPage;

	/**×¢²áÒ³Ãæ					by Mr.cao 20210223*/
	UWFY_MainPage* RegisterPage;


	
};
