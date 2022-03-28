
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TopTitle.generated.h"

class UTexture2D;
UCLASS()
class UUI_TopTitle : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PlayerName;

	UPROPERTY(meta = (BindWidget))
		class UImage* SpeakImage;

public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void SetTitle(FString Titile);

	void SetStateImage(UTexture2D* Image);

private:
	//UPROPERTY()
	UTexture2D* Speaking;

	//UPROPERTY()
	UTexture2D* NoSpeaker;
};

