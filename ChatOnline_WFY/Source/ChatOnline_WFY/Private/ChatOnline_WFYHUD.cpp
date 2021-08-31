// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatOnline_WFYHUD.h"
//#include <UMG/Public/Blueprint/UserWidget.h>
#include <Engine/Engine.h>
//#include "WFY_MainPage.h"
#include "Kismet/GameplayStatics.h"

void AChatOnline_WFYHUD::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("BeginPlay"));

	//UWFY_MainPage* WFY_MainPage = CreateWidget<UWFY_MainPage>(GetWorld(), WidgetClass);

	//if (WFY_MainPage !=nullptr)
	//{
	//	WFY_MainPage->AddToViewport();

	//	//FPlatformProcess::Sleep(2.0f);
	//	//FPlatformProcess::SleepNoStats(2.0f);

	//	if (WFY_MainPage->GetInitLoadPage())
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Delay"));
	//		WFY_MainPage->GetInitLoadPage()->SetVisibility(ESlateVisibility::Hidden);
	//	}
	//	

	//}

	APlayerController* myPlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (myPlayerController != nullptr)
	{
		myPlayerController->bShowMouseCursor = true;

		FInputModeGameAndUI myInputMode;

		//myInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

		myPlayerController->SetInputMode(myInputMode);
	}
}
