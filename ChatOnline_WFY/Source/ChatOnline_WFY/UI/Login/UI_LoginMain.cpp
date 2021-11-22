

// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_LoginMain.h"
#include "UI_Register.h"
#include "UI_Login.h"
//#include "UI_ServerIn.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"

void UUI_LoginMain::NativeConstruct()
{
	Super::NativeConstruct();

	UI_Login->SetParents(this);
	UI_Register->SetParents(this);
	//UI_ServerIn->SetParents(this);

	OpenMainUI();
}

void UUI_LoginMain::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_LoginMain::OpenMainUI()
{
	PlayAnimation(GetNameWidgetAnimation(TEXT("MainIn")));
}

void UUI_LoginMain::CloseMainUI()
{
	UWidgetAnimation* OutAnimation = GetNameWidgetAnimation(TEXT("MainOut"));

	if (OutAnimation)
	{
		//if (!OutAnimation->OnAnimationFinished.Contains(this, TEXT("MainOutAnimationFinish")))
		//{
		//	OutAnimation->OnAnimationFinished.AddDynamic(this, &UH_UI_LoginMain::MainOutAnimationFinish);
		//}

		FWidgetAnimationDynamicEvent WidgetAnimationDynamicEvent;
		WidgetAnimationDynamicEvent.BindDynamic(this, &UUI_LoginMain::MainOutAnimationFinish);
		UnbindFromAnimationFinished(OutAnimation, WidgetAnimationDynamicEvent);
		BindToAnimationFinished(OutAnimation, WidgetAnimationDynamicEvent);

		PlayAnimation(OutAnimation);
	}
}

void UUI_LoginMain::OpenLoginUI()
{
	PlayAnimation(GetNameWidgetAnimation(TEXT("LoginIn")));
}

void UUI_LoginMain::CloseLoginUI()
{
	UWidgetAnimation* OutAnimation = GetNameWidgetAnimation(TEXT("LoginOut"));

	if (OutAnimation)
	{
		//if (!OutAnimation->OnAnimationFinished.Contains(this, TEXT("LoginOutAnimationFinish")))
		//{
		//	OutAnimation->OnAnimationFinished.AddDynamic(this, &UH_UI_LoginMain::LoginOutAnimationFinish);
		//}

		/*FWidgetAnimationDynamicEvent WidgetAnimationDynamicEvent;
		WidgetAnimationDynamicEvent.BindDynamic(this, &UUI_LoginMain::LoginOutAnimationFinish);
		UnbindFromAnimationFinished(OutAnimation, WidgetAnimationDynamicEvent);
		BindToAnimationFinished(OutAnimation, WidgetAnimationDynamicEvent);

		PlayAnimation(OutAnimation);*/
	}
}

void UUI_LoginMain::OpenRegisterUI()
{


	UI_Login->SetVisibility(ESlateVisibility::Hidden);
	UI_Register->SetVisibility(ESlateVisibility::Visible);
	//PlayAnimation(GetNameWidgetAnimation(TEXT("BlurIn")));
}

void UUI_LoginMain::CloseRegisterUI()
{

	UI_Login->SetVisibility(ESlateVisibility::Visible);
	UI_Register->SetVisibility(ESlateVisibility::Hidden);
	//PlayAnimation(GetNameWidgetAnimation(TEXT("BlurOut")));
}

void UUI_LoginMain::OpenServerUI()
{
	//PlayAnimation(GetNameWidgetAnimation(TEXT("ServerMainIn")));
}

void UUI_LoginMain::CloseServerUI()
{
	//PlayAnimation(GetNameWidgetAnimation(TEXT("ServerMainOut")));
}

void UUI_LoginMain::OpenServerList()
{

}

void UUI_LoginMain::CloseServerList()
{

}

void UUI_LoginMain::MainOutAnimationFinish()
{
	//½øÈë´óÌü
	//ULoginGameInstance *LoginGameInstance = GetWorld()->GetGameInstance<ULoginGameInstance>();
	//if (LoginGameInstance)
	//{
	//	LoginGameInstance->OpenHallLevel();
	//}
}

void UUI_LoginMain::LoginOutAnimationFinish()
{
	//OpenServerUI();
}

//void UUI_LoginMain::AddSeverList(uint8 InType, const TArray<struct FGateInfo>& InNetInfo)
//{
//	//UI_ServerIn->AddSeverList(InType, InNetInfo);
//}
