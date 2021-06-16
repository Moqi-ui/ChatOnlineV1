/*********************************************************
* @copyright		2020 - 2021, www.imrcao.com, Ltd.All right reserved
*
* @author			imrcao
* 
* @date				2021/4/8-21:09
* 
* @brief			用户登录管理器，为单例
* 
* @see
*
* @note
**********************************************************/


#pragma once
#include "CoreMinimal.h"
#include "Tickable.h"
#include "UserDataManagerTool.h"

class CHATONLINE_WFY_API FUserLandManager:public FTickableGameObject
{
	struct FVerificationCode
	{
		FString code;

		FString identifier;

		FDateTime time;


		FVerificationCode()
		{

		}

		FVerificationCode(FString code_, FString identifier_)
			:code(code_), identifier(identifier_), time(FDateTime::Now())
		{

		}

		static FString ContructVerificationCode();

		static bool Verification(const FVerificationCode code, FString identifier, FString VerificationCode);

	};

public:

	virtual void Tick(float DaltaTime)override;

	virtual ETickableTickType GetTickableTickType() const override;

	virtual TStatId GetStatId() const override;



public:

	static FUserLandManager* Get();

	bool GetUserLandStat() const
	{
		return bIsUserLand;
	}

	FDMUserData GetCurrentUserData() const
	{
		return CurrentUserInfoData;
	}

	bool TryLandWithPassword(FString identity_Type, FString identifier, FString userInputPassword, FString &err);

	bool TryLandWithVerificationCode(FString identifier, FString VerificationCode, FString& err);

	bool TryModificationPassword(int userId, FString NewPassword, FString& err);

	bool TrySendOneVerificationCode(FString identity_Type, FString ienditifier, FString& err);

	bool TryRegisterOneUser(FDMUserData userInfoData, FString password, FString verificationCode, FString& err);

	void Logout();

	bool JudgePhoneNumberFormat(FString strPhoneNumber);

	bool JudgePhoneNumberBisExist(FString strPhoneNumber);

	bool JudgeInputPasswordFormat(FString inputPassword);

	bool JudgeVerificationCodeFormat(FString inputVerificationCode);

	bool JudgeVerificationValidty(FString identifier, FString userInputCode);

	bool JudgeAccidentExit(FString Identify);

	bool JudgeUserNameFormat(FString inputUserName);

	FUserDataManagerTool GetUserDataManagerTool();

	int GetLoginStatus(FString identifity);

	int GetUserIDForIdentifier(FString identifier);


public:

	//心跳间隔时间
	const static int heartBeatTime = 30;

	FString CurrentUserInputPhoneNumber;



private:

	FUserLandManager();

	~FUserLandManager();

	void HeartBeatUser();

	bool UserLand(int userID);

	//数据加密
	void DataEncryption(FString inputData, FString& outputData);

private:

	static FUserLandManager* userLandManager;

	bool bIsUserLand = false;

	FDMUserData CurrentUserInfoData;

	FDateTime lastLandTime;

	FVerificationCode newVerificationCode;

	//登录客户端的唯一ID  by imrcao 20210422
	FString workID;

	FUserDataManagerTool userDataManagerTool;// = FUserDataManagerTool();

};