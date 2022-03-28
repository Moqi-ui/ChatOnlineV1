#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserInfo.generated.h"

UENUM()
enum class EUserState : uint8
{
	EOffline,
	EInHall,
	EInRoom
};

USTRUCT(BlueprintType)
struct CHATONLINE_WFY_API FUserInfo
{
	GENERATED_BODY()

	/**�û�Ψһid */
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		int userID;

	//�û����ڷ���ID
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		int RoomID;

	//�û�״̬
	UPROPERTY(BlueprintReadOnly, Category = "UserIfor")
		EUserState userState;

	/**�û��ǳ�*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userName;

	/**�ֻ���*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userPhoneNumber;

	/**�û�Ȩ��*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userPower;

	/**�û�ͷ�����ص�ַ*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userAvatar;

	/**�û�ע��ʱ��*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FDateTime userRegister;

	/**ֱ�ӹ���һ�㲻ʹ��
	*/
	FUserInfo();

	/**����һ���û�����
	*/
	//FUserInfo(int userid, int Roomid, FString name, FString Phone, FString upower, FString uAvatar, FDateTime uRegister);

	bool IsValue()const
	{
		return userID >= 1 && userName.Len() >= 2 && userPower.Len() >= 2;
	}
};