
/*********************************************************
* @copyright		2020 - 2021, www.imrcao.com, Ltd.All right reserved
*
* @author			imrcao
*
* @date				2021/4/8-22:09
*
* @brief			用户数据信息管理工具
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

	/**注册一个新的用户，将用户数据存入数据库					by moqi 20190926
	*@param						OneUserDate					一个用户的基本数据
	*@param						Password					用户密码
	*@param						workID						当前登陆的客户端ID
	*/
	bool RegisterNewUser(FDMUserData OneUserData, FString Password, FString workID);






	//bool QueryLinkResultTest1();

private:

	TSharedPtr<FSimpleMysqlLink> pDataBaseLinkName;

};