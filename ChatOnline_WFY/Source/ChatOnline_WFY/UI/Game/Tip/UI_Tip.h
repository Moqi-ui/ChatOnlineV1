// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_Base.h"
#include "UI_Tip.generated.h"

/**
 * 
 */
//UCLASS()
//class CHATONLINE_WFY_API UUI_Tip : public UUI_Base
//{
//	GENERATED_BODY()
//	
//};
//
//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "../../Core/UI_Base.h"
//#include "UI_Tip.generated.h"

class URichTextBlock;
class UTextBlock;
UCLASS()
class CHATONLINE_WFY_API UUI_Tip : public UUI_Base
{
	GENERATED_BODY()

		UPROPERTY(meta = (BindWidget))
		UTextBlock* DescribeText;

	UPROPERTY(meta = (BindWidget))
		URichTextBlock* RichTextAction;

	UPROPERTY(meta = (BindWidget))
		URichTextBlock* RichTextActive;

	UPROPERTY(meta = (BindWidget))
		URichTextBlock* RichTextPassive;

public:
	void SetDescribeText(const FText& InText);
	void SetTextAction(const FText& InText);
	void SetTextActive(const FText& InText);
	void SetTextPassive(const FText& InText);
};

