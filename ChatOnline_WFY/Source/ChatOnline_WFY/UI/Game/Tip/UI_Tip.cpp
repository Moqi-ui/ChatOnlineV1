// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Tip.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"

void UUI_Tip::SetDescribeText(const FText& InText)
{
	DescribeText->SetText(InText);
}

void UUI_Tip::SetTextAction(const FText& InText)
{
	RichTextAction->SetText(InText);
}

void UUI_Tip::SetTextActive(const FText& InText)
{
	RichTextActive->SetText(InText);
}

void UUI_Tip::SetTextPassive(const FText& InText)
{
	RichTextPassive->SetText(InText);
}