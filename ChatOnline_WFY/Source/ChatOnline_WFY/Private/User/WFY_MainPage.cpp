// Fill out your copyright notice in the Description page of Project Settings.


#include "WFY_MainPage.h"
#include <Kismet/GameplayStatics.h>
#include "../Public/VoiceControlSystem.h"
#include <Engine/Engine.h>

bool UWFY_MainPage::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/**��ȡ����UI�����ʵ��*/
	iniLoadPage = (UWFY_MainPage*)GetWidgetFromName(TEXT("InitLoadPage"));
	LoginPage = (UWFY_MainPage*)GetWidgetFromName(TEXT("LoginPage"));
	RegisterPage = (UWFY_MainPage*)GetWidgetFromName(TEXT("RegisterPage"));

	VoiceController = NewObject<UVoiceControlSystem>();

	if (!VoiceController)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Yellow, "WFY_MainPage->VoiceChontroller is nullptr!");
	}


	return true;
}

UWFY_MainPage* UWFY_MainPage::GetInitLoadPage()
{
	if (iniLoadPage)
	{
		return iniLoadPage;
	}
	return nullptr;
}

UVoiceControlSystem* UWFY_MainPage::GetOrCreateVoiceController()
{
	if (VoiceController != nullptr)
	{
		return VoiceController;
	}
	return nullptr;
}

bool UWFY_MainPage::TryLoginGame()
{

	//������Ѷ�Ʒ�������ַ
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("81.70.169.65:7777")));



	return false;
}

void UWFY_MainPage::ClickRegisterButton()
{

}

void UWFY_MainPage::ClickForgetPassword()
{

}
