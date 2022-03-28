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

	/**用户唯一id */
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		int userID;

	//用户所在房间ID
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		int RoomID;

	//用户状态
	UPROPERTY(BlueprintReadOnly, Category = "UserIfor")
		EUserState userState;

	/**用户昵称*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userName;

	/**手机号*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userPhoneNumber;

	/**用户权限*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userPower;

	/**用户头像下载地址*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FString userAvatar;

	/**用户注册时间*/
	UPROPERTY(BlueprintReadOnly, Category = "UserInfo")
		FDateTime userRegister;

	/**直接构造一般不使用
	*/
	FUserInfo();

	/**构造一个用户数据
	*/
	//FUserInfo(int userid, int Roomid, FString name, FString Phone, FString upower, FString uAvatar, FDateTime uRegister);

	bool IsValue()const
	{
		return userID >= 1 && userName.Len() >= 2 && userPower.Len() >= 2;
	}
};