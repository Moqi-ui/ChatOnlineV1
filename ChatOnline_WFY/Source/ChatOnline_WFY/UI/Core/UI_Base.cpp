// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"
//#include "../../MobyGamePlayerState.h"
//#include "MobyGame/MobyGameState.h"
#include "Animation/WidgetAnimation.h"
#include "../Game/Tip/UI_Tip.h"


UUI_Base::UUI_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TipPtr = NULL;
}

UWidgetAnimation* UUI_Base::GetNameWidgetAnimation(const FString& WidgetAnimationName) const
{
	/*if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;
		UWidgetAnimation** MyTempAnimation = TArrayAnimations.FindByPredicate([&](const UWidgetAnimation* OurAnimation) {return OurAnimation->GetFName().ToString() == (WidgetAnimationName + FString("_INST")); });
		return *MyTempAnimation;
	}*/

	return nullptr;
}

//AMobyGameHUD* UUI_Base::GetHUD()
//{
//	return Cast<AMobyGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
//}
//
//AMobyGamePlayerState* UUI_Base::GetPlayerState()
//{
//	return GetWorld()->GetFirstPlayerController()->GetPlayerState<AMobyGamePlayerState>();
//}
//
//AMobyGameState* UUI_Base::GetGameState()
//{
//	return GetWorld()->GetGameState<AMobyGameState>();
//}

//void UUI_Base::SetPlayerID(int64 InPlayerID)
//{
//	PlayerID = InPlayerID;
//}

UWidget* UUI_Base::GetTip()
{
	if (!TipPtr)
	{
		if (TipClass)
		{
			TipPtr = CreateWidget<UUI_Tip>(GetWorld(), TipClass);
		}
	}

	return TipPtr;
}