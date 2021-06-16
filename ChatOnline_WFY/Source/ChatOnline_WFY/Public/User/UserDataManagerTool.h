
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

class FUserDataManagerTool
{
public:

	FUserDataManagerTool();

	~FUserDataManagerTool();

	void setSqlLink(TSharedPtr<FSimpleMysqlLink> Link_);

public:

	/**ע��һ���µ��û������û����ݴ������ݿ�					by moqi 20190926
	*@param						OneUserDate					һ���û��Ļ�������
	*@param						Password					�û�����
	*@param						workID						��ǰ��½�Ŀͻ���ID
	*/
	bool RegisterNewUser(FDMUserData OneUserData, FString Password, FString workID);






	//bool QueryLinkResultTest1();

private:

	TSharedPtr<FSimpleMysqlLink> pDataBaseLinkName;

};