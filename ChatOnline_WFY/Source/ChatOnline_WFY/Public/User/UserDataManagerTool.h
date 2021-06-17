
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

class FUserDateManageTool
{
public:

	FUserDateManageTool();

	~FUserDateManageTool();

	void setSqlLink(TSharedRef<FSimpleMysqlLink> Link_);

public:

	/**注册一个新的用户，将用户数据存入数据库					by moqi 20190926
	*@param						OneUserDate					一个用户的基本数据
	*@param						Password					用户密码
	*@param						workID						当前登陆的客户端ID
	*/
	bool RegisterNewUser(FDMUserData OneUserData, FString Password, FString workID);

	/**判断用户输入的手机号是否注册过							by moqi 20190927
	*@param						PhoneNumber					用户输入的手机号
	*/
	bool JudgeOnePhoneNumberExist(FString PhoneNumber);

	/**如果手机号注册过，根据手机号查询对应的密码				by moqi 20190927
	*@param						PhoneNumber					用户输入的手机号
	*@param						Password					数据库中的密码原文
	*/
	bool GetDataBasePassword(FString PhoneNumber, FString& Password);

	/**如果手机号注册过，获得用户的登录状态						by moqi 20190927
	*@param						PhoneNumber					用户输入的手机号
	*RETURN													0-未登录；1-在线；2-从未登录过
	*/
	int GetUserLoggingStatus(FString PhoneNumber);

	/**登录的时候更新用户的登录状态,包括登录状态，最后登录时间，更新的登录时间		by moqi 20190927
	*@param						workID						当前登陆的客户端ID
	*@param						Identity					登录账号
	*@param						userID						用户ID
	*RETURN													是否更新成功
	*/
	bool UpdateUserLoginStatus(FString workID, FString Identity, int& userID);

	/**获得一个用户的基本信息									by moqi 20190928
	*@param						OneUserData					用户的基本信息
	*@param						userid						用户ID
	*RETURN													是否获取成功
	*/
	bool GetOneUserBaseData(FDMUserData& OneUserData, int userid);

	/**用户登出时更新登录状态									by moqi 20190928
	*RETURN													是否更新成功
	*/
	bool UpdateUserLogoutStatus(int userID);

	/**更新登录时间，用于捕捉意外登录的情况，每隔三十秒更细一次	by moqi 20190928
	*userID													用户ID
	*RETURN													是否更新成功
	*/
	bool UpdateUserLoginTIme(int userID);

	/**获得最后更新的时间	，用于判断是否为意外退出				by moqi 20190928
	*Identify												用户登录名
	*RETURN													是否获得成功
	*/
	bool UpdateUserLoginTIme(FString Identify, int64& Time);

	/**获得当前用户的密码										by moqi 20190928
	*userID													用户ID
	*RETURN													是否获得成功
	*/
	FString GetCurrentUserPassword(int userID);

	/**修改当前用户的密码										by moqi 20190928
	*@param						userID						用户ID
	*RETURN													是否修改成功
	*/
	bool ModifyCurrentUserPassword(int userID, FString NewPassword);

	/**根据登录名尝试获取用户ID								by moqi 20190928
	* @param					Identifier					用户登录名称
	*/
	int GetUserIDWithIdentifier(FString Identifier);

	/**解决Hash值溢出
	*
	*/
	static FString uitoa(uint32 n);




	//bool QueryLinkResultTest1();

private:

	TSharedPtr<FSimpleMysqlLink> pDataBaseLinkName;

	//用户相关表名称

	FString users_TableName = "users";

	FString user_land_TableName = "user_land";

	FString user_auths_TableName = "user_auths";


};