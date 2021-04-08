// Fill out your copyright notice in the Description page of Project Settings.

/*********************************************************
* @copyright		2020 - 2021, DreamMaster.Co, Ltd.All right reserved
*
* @author			imrcao
* @date				2021/4/8-21:09
* @brief			�û���¼�ӿ�
* @see
*
* @note
**********************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LoginRegisterInterface.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Category = "LoginRegister")
class CHATONLINE_WFY_API ULoginRegisterInterface : public UObject
{
	GENERATED_BODY()
	

private:

	virtual void PostInitProperties() override;


public:

	UFUNCTION(BlueprintCallable, Category = "ULoginRegister")
		void Print_F(FString InputStr);


};
