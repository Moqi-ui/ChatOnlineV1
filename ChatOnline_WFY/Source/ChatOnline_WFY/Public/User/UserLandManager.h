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
	/**验证码参数结构体*/
	struct FVerificationCode
	{
		/**验证码原文		by moqi	2019.09.24
		*/
		FString Code;

		/**对应的账号信息手机号或邮箱		by moqi	2019.09.24
		*/
		FString identifier;

		/**生成时间			by moqi	2019.09.24
		*/
		FDateTime time;

		FVerificationCode()
		{

		}

		/**构造一个验证码
		*/
		FVerificationCode(FString Code_, FString identifier_)
			:Code(Code_), identifier(identifier_), time(FDateTime::Now())
		{

		}


		/**随机生成一个6位验证码 	by moqi	2019.09.24
		*/
		static FString RandomNewVerificationCode();

		/**验证验证码是否有效	 by moqi	2019.09.24
		*	@	param code					当前验证码
		*	@	param identifier			验证手机号或邮箱
		*	@	param verificationCode		用户输入的验证码
		*	RETUEN		返回是否有效
		*/
		static bool Verification(const FVerificationCode& code, FString identifier, FString verificationCode);

	};

public:

	/**心跳间隔时间		by moqi	2019.09.24
	*/
	const static int  heartbeatTime = 30;

	/**实现基类tick方法  系统自动调用 不要手动调用		by moqi	2019.09.24
	*/
	virtual void Tick(float DeltaTime) override;

	virtual ETickableTickType GetTickableTickType() const override;

	/**实现基类GetStatId方法	by moqi	2019.09.24
	*/
	virtual TStatId GetStatId() const override;

	//~FUserLandManager();

	//当前用户输入的手机号（用于点击忘记密码按钮时，存入用户输入的手机号）
	FString CurrentInputPhnoeNumber;

public:

	/**获取控制器实例	by moqi	2019.09.24
	*/
	static FUserLandManager* Get();


	/*查询当前是否有用户登陆 by moqi	2019.09.24
	*/
	bool IsInUserLand() const
	{
		return isUserLand;
	}

	/*获取当前登陆的用户信息 by moqi	2019.09.24
	*/
	FDMUserData GetUserData()const
	{

		return landUser;
	}


	/**尝试使用账号密码登陆	 by moqi	2019.09.24
	*	@	param identity_type			账号类型  目前只有手机号  “Phone”
	*	@	param identifier			账号即手机号
	*	@	param credential			密码原文
	*	@	param err					返回的错误消息
	*	RETUEN		返回是否成功登陆
	*/
	bool TryLandFromPassword(FString identity_type, FString identifier, FString credential, FString& err);



	/**使用验证码登陆	 by moqi	2019.09.24
	*	@	param identifier			账号即手机号
	*	@	param verificationCode		用户输入的验证码
	*	@	param err					返回的错误消息
	*	RETUEN		返回是否成功登陆
	*/
	bool TryLandFromVerificationCode(FString identifier, FString verificationCode, FString& err);


	/**修改当前账号的密码				 by moqi	2019.09.24
	*	@	param userID			账号id
	*	@	param NewPassword		用户输入的新密码
	*	@	param err				返回的错误消息
	*	RETUEN		返回是否修改成功
	*/
	bool ChangePassword(int userID, FString NewPassword, FString& err);


	/**创建一个验证码			 by moqi	2019.09.24
	*	@	param identity_type		发送渠道类型   目前只实现 手机号
	*	@	param identifier		发送地址  即 手机号
	*	@	param err				返回的错误消息
	*	@	param SimpleHttpObj		by moqi 20190926
	*	RETUEN		是否生成成功
	*/
	bool MakeNewVerificationCode(FString identity_type, FString identifier, FString& err);


	/**注册一个新用户	by moqi	2019.09.24
	*	@	param userData			用户信息
	*	@	param Password			用户输入的密码
	*	@	param verificationCode	输入的验证码
	*	@	param err				返回的错误消息
	*	RETUEN						是否注册成功
	*/
	bool RegisterUser(FDMUserData userData, FString  Password, FString verificationCode, FString& err);



	/**用户登出	by moqi	2019.09.24
	*/
	void Logout();

	/**判断手机号格式是否符合规则						by moqi 20190925
	*@param							str				手机号
	*RETURN											手机号格式是否正确
	*/
	bool JudgePhoneNumberFormat(FString str);

	/**判断手机号是否已经注册（格式正确的情况下执行）	by moqi 20190925
	*@param							str				手机号
	*RETURN											手机号是否存在
	*/
	bool JudgePhoneNumberFIsRegister(FString str);

	/**判断用户输入的密码是否符合规则					by moqi 20190925
	*@param							str				用户输入的密码
	*RETURN											秘密是否符合规则
	*/
	bool JudgePasswordFormat(FString str);

	/**判断验证码格式是否正确							by moqi 20190925
	*@param							VerificationCode验证码
	*/
	bool JudgeVerificationCodeFormat(FString VerificationCode);

	/**判断姓名格式是否正确							by moqi 20190925
	*@param							UserName		验证码
	*/
	bool JudgeUserNameFormat(FString UserName);

	/**验证验证码有效性								by moqi 20190926
	*@param							identifier		用户输入的手机号
	*@param							UserInputCode	用户输入的验证码
	*RETURN											验证码是否有效
	*/
	bool VerificationCodeValidity(FString identifier, FString UserInputCode);

	/**返回用户数据管理工具							by moqi 20190925
	*RETURN											返回用户数据管理工具
	*/
	FUserDateManageTool GetUserDataManageTool();

	/**检测登录状态									by moqi 20190925
	*RETURN											返回登录状态
	*/
	int GetLoginStatus(FString identifity);

	void Print_F();


	/**判断是否为意外退出								by moqi 20190925
	*@param							UserName		验证码
	*/
	bool JudgeAccidentEixt(FString Identify);

	/**获取用户ID（用于点击忘记密码按钮时）				by moqi 201911018
	*@param							Identifier		登录名
	*/
	int GetUserIDForIdentifer(FString Identifier);

	FUserDateManageTool GetUserDataManagerTool();

private:

	/**用户管理器单例		by moqi	2019.09.24
	*/
	static FUserLandManager* userLandManager;


	/**当前是否有用户登陆		by moqi	2019.09.24
	*/
	bool			isUserLand = false;
	/**登陆的用户信息			by moqi	2019.09.24
	*/
	FDMUserData		landUser;

	/**上次更新时间			by moqi	2019.09.24
	*/
	FDateTime		updataTime;

	/**最后生成的验证码		by moqi	2019.09.24
	*/
	FVerificationCode nowVerificationCode;

	/**登陸客戶端的唯一ID		by moqi	2019.09.27
	*/
	FString workID;


	//实例化U类对象UMK_SimpleHttpObj								by moqi 20190926
	//UMK_SimpleHttpObj* simpleHttpObj;

	//用户数据管理工具，管理sql语句
	FUserDateManageTool UserDateManage;

	/**私有化构造		by moqi	2019.09.24
	*/
	FUserLandManager();

	/**执行心跳   定时更新登陆状态作为是否异常退出的判断	by moqi	2019.09.24
	*/
	void HeartbeatUser();

	/**用户登陆		by moqi	2019.09.24
	*/
	bool UserLand(int userID);


	/**
	*
	*/
	void DataEncryption(FString InpuData, FString& outData);

};