//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "UI_CoreBase.h"

// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_CoreBase.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Slider.h"

void UUI_CoreBase::SetSliderBindFunction(USlider* TmpSlider)
{
	check(TmpSlider != nullptr);

	TmpSlider->OnValueChanged.AddDynamic(this, &UUI_CoreBase::ChangedValue);
}