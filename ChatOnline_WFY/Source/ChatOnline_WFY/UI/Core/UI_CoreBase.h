// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "UI/Core/UI_Base.h"
//#include "UI_CoreBase.generated.h"
//
///**
// * 
// */
//UCLASS()
//class CHATONLINE_WFY_API UUI_CoreBase : public UUI_Base
//{
//	GENERATED_BODY()
//	
//};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Base.h"
#include "UI_CoreBase.generated.h"
class FSimpleChannel;
class USlider;
UCLASS()
class UUI_CoreBase : public UUI_Base
{
	GENERATED_BODY()

public:

	template<class T>
	T* GetCurrentPlayerController()
	{
		if (GetWorld())
		{
			return Cast<T>(GetWorld()->GetFirstPlayerController());
		}
		return NULL;
	}

	template<class T>
	T* GetCurrentPawn()
	{
		if (GetWorld())
		{
			return Cast<T>(GetWorld()->GetFirstPlayerController()->GetPawn());
		}

		return NULL;
	}

	template<class T>
	T* GetCurrentHUD()
	{
		if (GetWorld() && GetWorld()->GetFirstPlayerController())
		{
			return  Cast<T>(GetWorld()->GetFirstPlayerController()->GetHUD());
		}
		return  NULL;
	}

	template<class T>
	T* GetCurrentGameInstance()
	{
		return GetWorld() != nullptr ? Cast<T>(GetWorld()->GetGameInstance()) : NULL;
	}

	template<class T>
	T* GetCurrentGameState()
	{
		return GetWorld() != nullptr ? Cast<T>(GetWorld()->GetGameState<T>()) : NULL;
	}

	template<class T>
	T* GetParents()
	{
		return Cast<T>(ParentsBase);
	}

	template<class TUseWidget, class TSlot>
	void SetWidgetZOrder(TUseWidget* NewUseWidget, int32 ZOrderIndex)
	{
		if (NewUseWidget)
		{
			TSlot* m_CanvasPanelSlot = Cast<TSlot>(NewUseWidget->Slot);

			if (m_CanvasPanelSlot)
			{
				m_CanvasPanelSlot->SetZOrder(ZOrderIndex);
			}
		}
	}

	template<class TUseWidget, class TSlot>
	int32 GetWidgetZOrder(TUseWidget* NewUseWidget)
	{
		int32 WidgetZOrder = INDEX_NONE;
		if (NewUseWidget)
		{
			TSlot* m_CanvasPanelSlot = Cast<TSlot>(NewUseWidget->Slot);

			if (m_CanvasPanelSlot)
			{
				WidgetZOrder = m_CanvasPanelSlot->GetZOrder();
			}
		}
		return WidgetZOrder;
	}

	void SetParents(UUI_CoreBase* m_Base) { ParentsBase = m_Base; }

	FORCEINLINE FGeometry GetGeometry() { return BaseGeometry; }
	FORCEINLINE UUI_CoreBase* GetParents() { return ParentsBase.Get(); }
protected:
	void SetSliderBindFunction(USlider* TmpSlider);

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) {}
	//½Ó¿Ú
protected:

	UFUNCTION()
		virtual void ChangedValue(float Val) {}

protected:

	FGeometry BaseGeometry;

private:
	TWeakObjectPtr<UUI_CoreBase> ParentsBase;
};
