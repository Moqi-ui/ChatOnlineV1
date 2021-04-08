
/*********************************************************
* @copyright		2020 - 2021, www.imrcao.com, Ltd.All right reserved
*
* @author			imrcao
*
* @date				2021/4/8-22:09
*
* @brief			用户数据结构
*
* @see
*
* @note
**********************************************************/


#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserDataType.generated.h"

USTRUCT(BlueprintType)
struct CHATONLINE_WFY_API FUserDataType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		int userID;

	FUserDataType();
};