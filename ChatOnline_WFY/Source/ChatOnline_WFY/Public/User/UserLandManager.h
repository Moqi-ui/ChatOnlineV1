/*********************************************************
* @copyright		2020 - 2021, www.imrcao.com, Ltd.All right reserved
*
* @author			imrcao
* 
* @date				2021/4/8-21:09
* 
* @brief			�û���¼��������Ϊ����
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
	/**��֤������ṹ��*/
	struct FVerificationCode
	{
		/**��֤��ԭ��		by moqi	2019.09.24
		*/
		FString Code;

		/**��Ӧ���˺���Ϣ�ֻ��Ż�����		by moqi	2019.09.24
		*/
		FString identifier;

		/**����ʱ��			by moqi	2019.09.24
		*/
		FDateTime time;

		FVerificationCode()
		{

		}

		/**����һ����֤��
		*/
		FVerificationCode(FString Code_, FString identifier_)
			:Code(Code_), identifier(identifier_), time(FDateTime::Now())
		{

		}


		/**�������һ��6λ��֤�� 	by moqi	2019.09.24
		*/
		static FString RandomNewVerificationCode();

		/**��֤��֤���Ƿ���Ч	 by moqi	2019.09.24
		*	@	param code					��ǰ��֤��
		*	@	param identifier			��֤�ֻ��Ż�����
		*	@	param verificationCode		�û��������֤��
		*	RETUEN		�����Ƿ���Ч
		*/
		static bool Verification(const FVerificationCode& code, FString identifier, FString verificationCode);

	};

public:

	/**�������ʱ��		by moqi	2019.09.24
	*/
	const static int  heartbeatTime = 30;

	/**ʵ�ֻ���tick����  ϵͳ�Զ����� ��Ҫ�ֶ�����		by moqi	2019.09.24
	*/
	virtual void Tick(float DeltaTime) override;

	virtual ETickableTickType GetTickableTickType() const override;

	/**ʵ�ֻ���GetStatId����	by moqi	2019.09.24
	*/
	virtual TStatId GetStatId() const override;

	//~FUserLandManager();

	//��ǰ�û�������ֻ��ţ����ڵ���������밴ťʱ�������û�������ֻ��ţ�
	FString CurrentInputPhnoeNumber;

public:

	/**��ȡ������ʵ��	by moqi	2019.09.24
	*/
	static FUserLandManager* Get();


	/*��ѯ��ǰ�Ƿ����û���½ by moqi	2019.09.24
	*/
	bool IsInUserLand() const
	{
		return isUserLand;
	}

	/*��ȡ��ǰ��½���û���Ϣ by moqi	2019.09.24
	*/
	FDMUserData GetUserData()const
	{

		return landUser;
	}


	/**����ʹ���˺������½	 by moqi	2019.09.24
	*	@	param identity_type			�˺�����  Ŀǰֻ���ֻ���  ��Phone��
	*	@	param identifier			�˺ż��ֻ���
	*	@	param credential			����ԭ��
	*	@	param err					���صĴ�����Ϣ
	*	RETUEN		�����Ƿ�ɹ���½
	*/
	bool TryLandFromPassword(FString identity_type, FString identifier, FString credential, FString& err);



	/**ʹ����֤���½	 by moqi	2019.09.24
	*	@	param identifier			�˺ż��ֻ���
	*	@	param verificationCode		�û��������֤��
	*	@	param err					���صĴ�����Ϣ
	*	RETUEN		�����Ƿ�ɹ���½
	*/
	bool TryLandFromVerificationCode(FString identifier, FString verificationCode, FString& err);


	/**�޸ĵ�ǰ�˺ŵ�����				 by moqi	2019.09.24
	*	@	param userID			�˺�id
	*	@	param NewPassword		�û������������
	*	@	param err				���صĴ�����Ϣ
	*	RETUEN		�����Ƿ��޸ĳɹ�
	*/
	bool ChangePassword(int userID, FString NewPassword, FString& err);


	/**����һ����֤��			 by moqi	2019.09.24
	*	@	param identity_type		������������   Ŀǰֻʵ�� �ֻ���
	*	@	param identifier		���͵�ַ  �� �ֻ���
	*	@	param err				���صĴ�����Ϣ
	*	@	param SimpleHttpObj		by moqi 20190926
	*	RETUEN		�Ƿ����ɳɹ�
	*/
	bool MakeNewVerificationCode(FString identity_type, FString identifier, FString& err);


	/**ע��һ�����û�	by moqi	2019.09.24
	*	@	param userData			�û���Ϣ
	*	@	param Password			�û����������
	*	@	param verificationCode	�������֤��
	*	@	param err				���صĴ�����Ϣ
	*	RETUEN						�Ƿ�ע��ɹ�
	*/
	bool RegisterUser(FDMUserData userData, FString  Password, FString verificationCode, FString& err);



	/**�û��ǳ�	by moqi	2019.09.24
	*/
	void Logout();

	/**�ж��ֻ��Ÿ�ʽ�Ƿ���Ϲ���						by moqi 20190925
	*@param							str				�ֻ���
	*RETURN											�ֻ��Ÿ�ʽ�Ƿ���ȷ
	*/
	bool JudgePhoneNumberFormat(FString str);

	/**�ж��ֻ����Ƿ��Ѿ�ע�ᣨ��ʽ��ȷ�������ִ�У�	by moqi 20190925
	*@param							str				�ֻ���
	*RETURN											�ֻ����Ƿ����
	*/
	bool JudgePhoneNumberFIsRegister(FString str);

	/**�ж��û�����������Ƿ���Ϲ���					by moqi 20190925
	*@param							str				�û����������
	*RETURN											�����Ƿ���Ϲ���
	*/
	bool JudgePasswordFormat(FString str);

	/**�ж���֤���ʽ�Ƿ���ȷ							by moqi 20190925
	*@param							VerificationCode��֤��
	*/
	bool JudgeVerificationCodeFormat(FString VerificationCode);

	/**�ж�������ʽ�Ƿ���ȷ							by moqi 20190925
	*@param							UserName		��֤��
	*/
	bool JudgeUserNameFormat(FString UserName);

	/**��֤��֤����Ч��								by moqi 20190926
	*@param							identifier		�û�������ֻ���
	*@param							UserInputCode	�û��������֤��
	*RETURN											��֤���Ƿ���Ч
	*/
	bool VerificationCodeValidity(FString identifier, FString UserInputCode);

	/**�����û����ݹ�����							by moqi 20190925
	*RETURN											�����û����ݹ�����
	*/
	FUserDateManageTool GetUserDataManageTool();

	/**����¼״̬									by moqi 20190925
	*RETURN											���ص�¼״̬
	*/
	int GetLoginStatus(FString identifity);

	void Print_F();


	/**�ж��Ƿ�Ϊ�����˳�								by moqi 20190925
	*@param							UserName		��֤��
	*/
	bool JudgeAccidentEixt(FString Identify);

	/**��ȡ�û�ID�����ڵ���������밴ťʱ��				by moqi 201911018
	*@param							Identifier		��¼��
	*/
	int GetUserIDForIdentifer(FString Identifier);

	FUserDateManageTool GetUserDataManagerTool();

private:

	/**�û�����������		by moqi	2019.09.24
	*/
	static FUserLandManager* userLandManager;


	/**��ǰ�Ƿ����û���½		by moqi	2019.09.24
	*/
	bool			isUserLand = false;
	/**��½���û���Ϣ			by moqi	2019.09.24
	*/
	FDMUserData		landUser;

	/**�ϴθ���ʱ��			by moqi	2019.09.24
	*/
	FDateTime		updataTime;

	/**������ɵ���֤��		by moqi	2019.09.24
	*/
	FVerificationCode nowVerificationCode;

	/**��ꑿ͑��˵�ΨһID		by moqi	2019.09.27
	*/
	FString workID;


	//ʵ����U�����UMK_SimpleHttpObj								by moqi 20190926
	//UMK_SimpleHttpObj* simpleHttpObj;

	//�û����ݹ����ߣ�����sql���
	FUserDateManageTool UserDateManage;

	/**˽�л�����		by moqi	2019.09.24
	*/
	FUserLandManager();

	/**ִ������   ��ʱ���µ�½״̬��Ϊ�Ƿ��쳣�˳����ж�	by moqi	2019.09.24
	*/
	void HeartbeatUser();

	/**�û���½		by moqi	2019.09.24
	*/
	bool UserLand(int userID);


	/**
	*
	*/
	void DataEncryption(FString InpuData, FString& outData);

};