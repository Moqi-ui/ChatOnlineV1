
#include "UserLandManager.h"

FUserLandManager* FUserLandManager::userLandManager = nullptr;



FUserLandManager::FUserLandManager()
	:bIsUserLand(false), lastLandTime(0)
{
	//FGuid UE4中的一个功能，能够生成一个唯一的字符。
	workID = FGuid::NewGuid().ToString();
}

FUserLandManager::~FUserLandManager()
{

}

void FUserLandManager::Tick(float DaltaTime)
{

}

ETickableTickType FUserLandManager::GetTickableTickType() const
{
	return ETickableTickType::Always;
}

TStatId FUserLandManager::GetStatId() const 
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FUserLandManager, STATGROUP_Tickables);
}

FString FUserLandManager::FVerificationCode::ContructVerificationCode()
{
	FString RandomVerificationCode;

	for (int i = 0; i<6; i++)
	{
		int num = FMath::RandRange(0, 9);

		RandomVerificationCode = FString::FromInt(num) + RandomVerificationCode;
	}

	return RandomVerificationCode;
}

bool FUserLandManager::FVerificationCode::Verification(FVerificationCode code, FString identifier, FString VerificationCode)
{
	if (code.identifier == identifier)
	{
		if (code.code == VerificationCode)
		{
			return true;
		}
	}
	return false;
}



FUserLandManager* FUserLandManager::Get()
{
	if (!userLandManager)
	{
		userLandManager = new FUserLandManager();
	}

	return userLandManager;

}

bool FUserLandManager::TryLandWithPassword(FString identity_Type, FString identifier, FString userInputPassword, FString& err)
{
	return false;
}

bool FUserLandManager::TryLandWithVerificationCode(FString identifier, FString VerificationCode, FString& err)
{
	return false;
}

bool FUserLandManager::TryModificationPassword(int userId, FString NewPassword, FString& err)
{
	return false;
}

bool FUserLandManager::TrySendOneVerificationCode(FString identity_Type, FString ienditifier, FString& err)
{
	return false;
}

bool FUserLandManager::TryRegisterOneUser(FUserInfoData userInfoData, FString password, FString verificationCode, FString& err)
{
	return false;
}

void FUserLandManager::Logout()
{

}

bool FUserLandManager::JudgePhoneNumberFormat(FString strPhoneNumber)
{
	return false;
}

bool FUserLandManager::JudgePhoneNumberBisExist(FString strPhoneNumber)
{
	return false;
}

bool FUserLandManager::JudgeInputPasswordFormat(FString inputPassword)
{
	return false;
}

bool FUserLandManager::JudgeVerificationCodeFormat(FString inputVerificationCode)
{
	return false;
}

bool FUserLandManager::JudgeVerificationValidty(FString identifier, FString userInputCode)
{
	return false;
}

bool FUserLandManager::JudgeAccidentExit(FString Identify)
{
	return false;
}

bool FUserLandManager::JudgeUserNameFormat(FString inputUserName)
{
	return false;
}

FUserDataManagerTool FUserLandManager::GetUserDataManagerTool()
{
	return userDataManagerTool;
}

int FUserLandManager::GetLoginStatus(FString identifity)
{
	return 0;
}

int FUserLandManager::GetUserIDForIdentifier(FString identifier)
{
	return 0;
}

void FUserLandManager::HeartBeatUser()
{

}

bool FUserLandManager::UserLand(int userID)
{
	return false;
}

void FUserLandManager::DataEncryption(FString inputData, FString& outputData)
{

}