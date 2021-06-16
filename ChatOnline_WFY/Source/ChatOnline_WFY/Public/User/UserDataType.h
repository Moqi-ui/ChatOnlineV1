
/*********************************************************
* @copyright		2020 - 2021, www.imrcao.com, Ltd.All right reserved
*
* @author			imrcao
*
* @date				2021/4/8-22:09
*
* @brief			�û����ݽṹ
*
* @see
*
* @note
**********************************************************/


#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserDataType.generated.h"


/**һ���û��Ļ������� ��Ӧ���ݿ⡰users����
 *
 */

USTRUCT(BlueprintType)
struct CHATONLINE_WFY_API FDMUserData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		int userID;

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userName;

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userPhoneNumber;

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userPower;

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userAvatar;

	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FDateTime userRegisterTime;

	FDMUserData();

	FDMUserData(int userID_, FString userName_, FString userPhoneNumber_, FString userPower_, FString userAvatar_, FDateTime userRegisterTime_);

	bool IsValue()const
	{
		return userID >= 1 && userName.Len() >= 2 && userPower.Len() >= 2;
	}

};