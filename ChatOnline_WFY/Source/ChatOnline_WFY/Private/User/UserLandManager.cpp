
#include "UserLandManager.h"
#include "UnrealMathUtility.h"
#include "Engine.h"
#include <string>
//#include <windows.h>
using namespace std;

FUserLandManager* FUserLandManager::userLandManager = nullptr;

FUserLandManager::FUserLandManager()
	:isUserLand(false)
	, updataTime(0)
{
	//simpleHttpObj = NewObject<UMK_SimpleHttpObj>(UMK_SimpleHttpObj::StaticClass());

	//FGuid UE4�е�һ�����ܣ��ܹ�����һ��Ψһ���ַ���
	workID = FGuid::NewGuid().ToString();
}

ETickableTickType FUserLandManager::GetTickableTickType() const
{
	return ETickableTickType::Always;
}

/**ʵ�ֻ���tick����  ϵͳ�Զ����� ��Ҫ�ֶ����� */
void FUserLandManager::Tick(float DeltaTime)
{
	//�����ǰ���û���¼
	if (isUserLand)
	{
		HeartbeatUser();

		//ʱ�̼���¼״̬�����ڶ�����һ�����Ե�¼��ͬһ���˺š�Ŀǰ�Ȳ�����
	}
}

/**ʵ�ֻ���GetStatId����*/
TStatId  FUserLandManager::GetStatId() const
{

	RETURN_QUICK_DECLARE_CYCLE_STAT(FUserLandManager, STATGROUP_Tickables);

}

FString FUserLandManager::FVerificationCode::RandomNewVerificationCode()
{
	FString RandomVerificationCode;

	for (int i = 0; i<6; i++)
	{
		int num = FMath::RandRange(0, 9);

		RandomVerificationCode = FString::FromInt(num) + RandomVerificationCode;
	}

	return RandomVerificationCode;
}

bool FUserLandManager::FVerificationCode::Verification(const FVerificationCode& code, FString identifier, FString verificationCode)
{
	if (code.identifier == identifier)
	{
		if (code.Code == verificationCode)
		{
			return true;
		}
	}
	return false;
}

FUserLandManager* FUserLandManager::Get()
{
	if (userLandManager)
	{
		return userLandManager;
	}

	return userLandManager = new FUserLandManager();
}

FUserDateManageTool FUserLandManager::GetUserDataManagerTool()
{
	return UserDateManage;
}

bool FUserLandManager::TryLandFromPassword(FString identity_type, FString identifier, FString credential, FString& err)
{
	//�ֻ��Ŷ�Ӧ���ݿ��е�ԭ������
	FString DataBasaPassword;

	UserDateManage.GetDataBasePassword(identifier, DataBasaPassword);

	FString outsr;

	DataEncryption(credential, outsr);

	//uint32 HashInputPassword = GetTypeHash(credential);

	//FString outsr = FUserDateManageTool::uitoa(HashInputPassword);

	//�ж��û�����������Ƿ���ȷ
	if (DataBasaPassword == outsr)
	{
		int userid;
		if (UserDateManage.UpdateUserLoginStatus(workID, identifier, userid))
		{

			if (UserLand(userid))
			{
				isUserLand = true;
				return true;
			}
		}
	}

	isUserLand = false;

	return false;
}

bool FUserLandManager::TryLandFromVerificationCode(FString identifier, FString verificationCode, FString& err)
{

	if (FVerificationCode::Verification(nowVerificationCode, identifier, verificationCode))
	{
		int userid;
		if (UserDateManage.UpdateUserLoginStatus(workID, identifier, userid))
		{

			if (UserLand(userid))
			{
				isUserLand = true;
				return true;
			}
		}
	}

	isUserLand = false;

	return false;
}

bool FUserLandManager::ChangePassword(int userID, FString NewPassword, FString& err)
{
	FString OldPassword = UserDateManage.GetCurrentUserPassword(userID);

	FString HashNewPassword;

	DataEncryption(NewPassword, HashNewPassword);

	if (OldPassword == HashNewPassword)
	{
		err = "TwopasswordEquality";
		return false;
	}

	if (UserDateManage.ModifyCurrentUserPassword(userID, HashNewPassword))
	{
		//��¼��ǰ�Ƿ����û���¼������޸ĳɹ������˳���ǰ��¼���Ҹ��µ�¼״̬

		UserDateManage.UpdateUserLogoutStatus(userID);
		isUserLand = false;

		return true;
	}


	return false;
}

bool FUserLandManager::MakeNewVerificationCode(FString identity_type, FString identifier, FString& err)
{
	//by moqi 20190926

	//FMKSimpleHttpRequestData SimpleHttpRequestData;

	FString URL = "https://smssh1.253.com/msg/send/json";

	nowVerificationCode.Code = FVerificationCode::RandomNewVerificationCode();

	nowVerificationCode.identifier = identifier;

	FString Data = FString::Printf(TEXT("{\"account\":\"N4513527\",\"password\":\"9WYUfJPBEtabb0\",\"msg\":\"��ѡ�Ҽҡ�������֤���ǣ�%s\",\"phone\":\"%s\"}"), *nowVerificationCode.Code, *identifier);

	TMap<FString, FString> HardMap;

	HardMap.Add("Content-Type", "application/json");

	HardMap.Add("User-Agent", "application/x-www-form-urlencoded;charset=utf-8");

	//SimpleHttpRequestData.typ = EMK_SimpleHttpPostTyp::POST;

	//SimpleHttpRequestData.data = Data;

	//SimpleHttpRequestData.url = URL;

	//SimpleHttpRequestData.hardMap = HardMap;

	/*if (simpleHttpObj)
	{
		simpleHttpObj->StartPost(SimpleHttpRequestData, err);

		GLog->Log(err);

		return true;
	}*/

	GLog->Log(err);

	return false;
}

bool FUserLandManager::RegisterUser(FDMUserData userData, FString  Password, FString verificationCode, FString& err)
{
	FString EncryptionData;

	//���ݼ���
	//DataEncryption(Password, EncryptionData);

	//return UserDateManage.RegisterNewUser(userData, EncryptionData, workID);
	return UserDateManage.RegisterNewUser(userData, Password, workID);
}

void FUserLandManager::Logout()
{
	if (UserDateManage.UpdateUserLogoutStatus(landUser.userID))
	{
		isUserLand = false;

	//	GLog->Log("�����˳�");
	}
	else
	{
		isUserLand = false;

	//	GLog->Log("�쳣�˳�");
	}
}

void FUserLandManager::HeartbeatUser()
{
	int64 CurrentTime = FDateTime::Now().ToUnixTimestamp() - 28800;

	int64 LastTime = updataTime.ToUnixTimestamp() - 28800;

	if (CurrentTime - LastTime > 30)
	{
		updataTime = FDateTime::Now();

		Print_F();

		UserDateManage.UpdateUserLoginTIme(landUser.userID);
	}
}

bool FUserLandManager::UserLand(int userID)
{
	//��õ�ǰ��¼�û�����Ϣ


	return UserDateManage.GetOneUserBaseData(landUser, userID);
}

void FUserLandManager::Print_F()
{
	FString str = "striii";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, str);
	}

}


bool FUserLandManager::JudgePhoneNumberFormat(FString str)
{
	//by moqi 20190926
	//�ֻ��Ÿ�ʽ��1������Ϊ11λ���֣�2����һλ����Ϊ1��3���ڶ�λ����Ϊ0��1��2��

	TArray<TCHAR> Number;

	Number = str.GetCharArray();

	int leng = Number.Num() - 1;

	if (leng == 11)
	{
		if (Number[0] == '1')
		{
			if (Number[1] != '0' && Number[1] != '1' && Number[1] != '2')
			{
				GLog->Log(FString::FromInt(leng));

				return true;
			}
		}
	}
	return false;
}

bool FUserLandManager::JudgePhoneNumberFIsRegister(FString str)
{
	//by moqi 20190927
	return UserDateManage.JudgeOnePhoneNumberExist(str);
}

bool FUserLandManager::JudgePasswordFormat(FString str)
{
	//by moqi 20190926
	//�����ʽ����֧����ĸ����Сд��+���֣�����6-10���ַ�

	int length = str.Len();

	if (length > 5 && length < 11)
	{
		return true;
	}

	return false;
}
bool FUserLandManager::JudgeVerificationCodeFormat(FString VerificationCode)
{
	//by moqi 20190926
	//��֤�������λ����
	//GConfig->SetString();
	//GConfig->GetString();
	if (VerificationCode.Len() == 6)
	{
		return true;
	}

	return false;
}

bool FUserLandManager::JudgeUserNameFormat(FString UserName)
{
	//by moqi 20190926
	//��֤���������15�����������ڣ�֧�����ġ���ĸ������

	int length = UserName.Len();

	if (length > 0 && length < 16)
	{
		return true;
	}

	return false;
}


bool FUserLandManager::VerificationCodeValidity(FString identifier, FString UserInputCode)
{
	return FUserLandManager::FVerificationCode::Verification(nowVerificationCode, identifier, UserInputCode);
}

FUserDateManageTool FUserLandManager::GetUserDataManageTool()
{

	return UserDateManage;
}

int FUserLandManager::GetLoginStatus(FString identifity)
{

	return UserDateManage.GetUserLoggingStatus(identifity);
}

bool FUserLandManager::JudgeAccidentEixt(FString Identify)
{
	int64 LastUpdateTime;

	int64 NowTime = FDateTime::Now().ToUnixTimestamp() - 28800;

	UserDateManage.UpdateUserLoginTIme(Identify, LastUpdateTime);

	LastUpdateTime = LastUpdateTime - 28800;

	if ((NowTime - LastUpdateTime) > 30)
	{
		//��Ϊ�����˳�
		return true;
	}
	return false;
}
int FUserLandManager::GetUserIDForIdentifer(FString Identifier)
{
	return UserDateManage.GetUserIDWithIdentifier(Identifier);
}

void FUserLandManager::DataEncryption(FString InpuData, FString& outData)
{
	FSHAHash data;

	FSHA1::HashBuffer(InpuData.GetCharArray().GetData(), InpuData.GetCharArray().Num(), data.Hash);

	outData = data.ToString();
}


