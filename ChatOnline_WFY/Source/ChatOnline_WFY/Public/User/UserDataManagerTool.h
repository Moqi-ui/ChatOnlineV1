
/*********************************************************
* @copyright		2020 - 2021, www.imrcao.com, Ltd.All right reserved
*
* @author			imrcao
*
* @date				2021/4/8-22:09
*
* @brief			�û�������Ϣ������
*
* @see
*
* @note
**********************************************************/

#pragma once
#include "CoreMinimal.h"
#include "Core/SimpleMysqlLink.h"
#include "UserDataType.h"

class FUserDateManageTool
{
public:

	FUserDateManageTool();

	~FUserDateManageTool();

	void setSqlLink(TSharedRef<FSimpleMysqlLink> Link_);

public:

	/**ע��һ���µ��û������û����ݴ������ݿ�					by moqi 20190926
	*@param						OneUserDate					һ���û��Ļ�������
	*@param						Password					�û�����
	*@param						workID						��ǰ��½�Ŀͻ���ID
	*/
	bool RegisterNewUser(FDMUserData OneUserData, FString Password, FString workID);

	/**�ж��û�������ֻ����Ƿ�ע���							by moqi 20190927
	*@param						PhoneNumber					�û�������ֻ���
	*/
	bool JudgeOnePhoneNumberExist(FString PhoneNumber);

	/**����ֻ���ע����������ֻ��Ų�ѯ��Ӧ������				by moqi 20190927
	*@param						PhoneNumber					�û�������ֻ���
	*@param						Password					���ݿ��е�����ԭ��
	*/
	bool GetDataBasePassword(FString PhoneNumber, FString& Password);

	/**����ֻ���ע���������û��ĵ�¼״̬						by moqi 20190927
	*@param						PhoneNumber					�û�������ֻ���
	*RETURN													0-δ��¼��1-���ߣ�2-��δ��¼��
	*/
	int GetUserLoggingStatus(FString PhoneNumber);

	/**��¼��ʱ������û��ĵ�¼״̬,������¼״̬������¼ʱ�䣬���µĵ�¼ʱ��		by moqi 20190927
	*@param						workID						��ǰ��½�Ŀͻ���ID
	*@param						Identity					��¼�˺�
	*@param						userID						�û�ID
	*RETURN													�Ƿ���³ɹ�
	*/
	bool UpdateUserLoginStatus(FString workID, FString Identity, int& userID);

	/**���һ���û��Ļ�����Ϣ									by moqi 20190928
	*@param						OneUserData					�û��Ļ�����Ϣ
	*@param						userid						�û�ID
	*RETURN													�Ƿ��ȡ�ɹ�
	*/
	bool GetOneUserBaseData(FDMUserData& OneUserData, int userid);

	/**�û��ǳ�ʱ���µ�¼״̬									by moqi 20190928
	*RETURN													�Ƿ���³ɹ�
	*/
	bool UpdateUserLogoutStatus(int userID);

	/**���µ�¼ʱ�䣬���ڲ�׽�����¼�������ÿ����ʮ���ϸһ��	by moqi 20190928
	*userID													�û�ID
	*RETURN													�Ƿ���³ɹ�
	*/
	bool UpdateUserLoginTIme(int userID);

	/**��������µ�ʱ��	�������ж��Ƿ�Ϊ�����˳�				by moqi 20190928
	*Identify												�û���¼��
	*RETURN													�Ƿ��óɹ�
	*/
	bool UpdateUserLoginTIme(FString Identify, int64& Time);

	/**��õ�ǰ�û�������										by moqi 20190928
	*userID													�û�ID
	*RETURN													�Ƿ��óɹ�
	*/
	FString GetCurrentUserPassword(int userID);

	/**�޸ĵ�ǰ�û�������										by moqi 20190928
	*@param						userID						�û�ID
	*RETURN													�Ƿ��޸ĳɹ�
	*/
	bool ModifyCurrentUserPassword(int userID, FString NewPassword);

	/**���ݵ�¼�����Ի�ȡ�û�ID								by moqi 20190928
	* @param					Identifier					�û���¼����
	*/
	int GetUserIDWithIdentifier(FString Identifier);

	/**���Hashֵ���
	*
	*/
	static FString uitoa(uint32 n);




	//bool QueryLinkResultTest1();

private:

	TSharedPtr<FSimpleMysqlLink> pDataBaseLinkName;

	//�û���ر�����

	FString users_TableName = "users";

	FString user_land_TableName = "user_land";

	FString user_auths_TableName = "user_auths";


};