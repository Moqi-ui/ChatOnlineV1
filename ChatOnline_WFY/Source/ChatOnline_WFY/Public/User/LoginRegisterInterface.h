// Fill out your copyright notice in the Description page of Project Settings.

/*********************************************************
* @copyright		2020 - 2021, DreamMaster.Co, Ltd.All right reserved
*
* @author			imrcao
* @date				2021/4/8-21:09
* @brief			用户登录接口
* @see
*
* @note
**********************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserLandManager.h"
#include "Userwidget.h"
#include "TextBlock.h"
//#include "Core/SimpleMysqlLink.h"
#include "LoginRegisterInterface.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Category = "LoginRegister")
class CHATONLINE_WFY_API ULoginRegisterInterface : public UObject
{
	GENERATED_BODY()
	

private:

	virtual void PostInitProperties() override;

private:

	/**用来接收提示语组件							by moqi 20190925*/
	UTextBlock* pMessageLoginPromptWord;

	/**用户登录界面工具							by moqi 20190925*/
	FUserLandManager* UserLandManager;

	/**用户输入的手机号							by moqi 201909026*/
	FString UserInputNumber;
	/**用户输入的密码								by moqi 201909026*/
	FString UserInputPassword;
	/**用户第二次输入的密码						by moqi 201909026*/
	FString SecondPassword;
	/**用户输入的验证码							by moqi 201909026*/
	FString UserInputVerification;
	/**用户输入的姓名								by moqi 201909026*/
	FString UserInputName;
	/**用来记录手机号格式是否正确					by moqi 20190926*/
	bool IsPhoneNumberFormat = false;
	/**用来记录密码格式是否正确					by moqi 20190926*/
	bool IsPasswordFormat = false;
	/**用来记录验证码格式是否正确					by moqi 20190926*/
	bool IsVerificationCodeFormat = false;
	/**用来记录用户名格式是否正确					by moqi 20190926*/
	bool IsUserNameFormat = false;
	/**用来记录用户两次输入的密码是否一致			by moqi 20190926*/
	bool IsPasswordEquality = false;

	FTimerHandle MyTimeHandle;

public:

	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void Print_F(FString InputStr);

	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void init();

	/**显示或创建一个控件								by imrcao 20210422
	*@param							SelfWidget		自身控件
	*@param							MyUserWidget	指定要创建的控件
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void ShowOrCreateOneWidget(UWidget* SelfWidget, TSubclassOf<UUserWidget> MyUserWidget);


	/**当用户输入完手机号后，根据情况进行反馈			by moqi 20190925
	*  如果输入内容不规范则进行则进行相应的提示
	*@param							PhoneNumber		用户输入的手机号
	*@param							IsLoginInterface用来记录是不是登录界面
	@RETURN											用户输入的格式是否正确
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnPhoneNumberCommit(FText PhoneNumber, bool IsLoginInterface);

	/**当用户输入完密码后，判断密码是否符合规则			by moqi 20190925
	*@param							Password		用户输入的密码
	*RETURN											输入的密码是否符合规范
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnInputPasswordCommit(FText Password);

	/**当用户输入完用户名后，判断用户名是否符合规则		bu moqi 20190925
	*@param							UserName		用户输入的用户名
	*RETURN											输入的用户名是否符合规范
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnInputUserNameCommit(FText UserName);

	/**点击“获取验证码按钮”执行						bu moqi 20190926
	*RETURN											是否获取成功
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnClickGetVerificationButton();

	/**点击退出登录按钮								by moqi 20190930*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void OnClickExistLoginButton();


	/*****************************账号密码登录界面调用的方法******************************/

	/**当用户点击登录按钮时执行						by moqi 20190925
	*RETURN											是否登录成功
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickPasswordLoginButton();

	/**设置变量TheButtonIsEnable,根据传入的按钮类型不同，执行不同逻辑	by moqi 20190926
	*@param							ButtonType						按钮类型
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetTheButtonIsEnable(FString ButtonType);

	/**设置“忘记密码”按钮是否红色高亮									by moqi 20191018
	*@param							ButtonType						按钮类型
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetForgetPasswordColor();

	/*****************************验证码登录界面调用的方法******************************/

	/**当用户点击验证码登录按钮时执行						by moqi 20190925
	*RETURN												是否登录成功
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickCodeLoginButton();


	/*****************************注册界面调用的方法******************************/

	/**当用户点击注册按钮时执行							by moqi 20190925
	*RETURN												是否注册成功
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickRegisterButton();

	/***************************** 修改密码界面调用的方法******************************/

	/**当打开修改密码界面，将当前用户的手机号默认填入输入框，且不能编辑				by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void OnModifyPasswordWidget();

	/**判断两次密码是否一致								by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool JudgePasswordEquality();

	/**当用户第二次输入密码完成							by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnUserSecondCommitPassword(FText SecondPassword);

	/**点击确认修改按钮执行								by moqi 20190930
	*RETURN												是否修改成功
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickConfirmModifyButton();

	/**根据手机格式设置获取验证码按钮的颜色和按钮是否能点击	by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetCodeButtonColorAndActive();

	/**设置获取验证码按钮为不可点击状态						by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetCodeButtonCanNotClick();

	/**设置获取验证码按钮为可点击状态					by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetCodeButtonCanClick();

	/**获得当前登录用户的用户名显示到UI						by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void ShowCurrentUserName();

	/**获得当前是否有用户登录									by moqi 20191018
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool GetIsInUserLand();



public:


	/**登录按钮的是否可点击								by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool TheButtonIsEnable = false;

	/**登录注册按钮的颜色									by moqi 20190926*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FLinearColor TheButtonBGColor = FLinearColor(FColor(0, 0, 0, 1));

	/**提示文字											by moqi 20190926*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText PromptWords;

	/**提示文字状态										by moqi 20190926*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TEnumAsByte<ESlateVisibility> PromptWordsState;

	/**当前用户的手机号									by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText CurrentUserPhoneNumber;

	/**获取验证码按钮的背景颜色							by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FLinearColor CodeButtonBGColor = FLinearColor(FColor(0, 0, 0, 1));

	/**获取验证码按钮的是否可点击							by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool CodeButtonIsEnable = false;

	/**获取获取当前登录用户的用户名						by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText CurrentUserName;

	/**忘记密码按钮的是否可点击（手机号注册过且未登录则可以点击忘记密码）	by moqi 20191017*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool ForgetPasswordButton = false;

	/**忘记密码颜色										by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FLinearColor ForgetTextColor = FLinearColor(FColor(0, 0, 0, 0.3));


public:

	//测试函数

	UFUNCTION(BlueprintCallable, Category = "UISQLtest")
		bool QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug);


	UFUNCTION(BlueprintCallable, Category = "UISQLtest")
		bool InsertTableDatasTest();



private:


	//FUserLandManager* UserLandManager;

	TSharedPtr<FSimpleMysqlLink> Link;

	/******************************数据库相关信息***************************/

	FString InUser = "root";

	FString InHost = "127.0.0.1";

	FString InPawd = "Mrcao";

	FString InDB = "wfy_database";

	uint32  InPort = 3306;

	FString Unix_Socket = TEXT("\0");

	TArray<ESimpleClientFlags> InClientFlag = TArray<ESimpleClientFlags>();

	/******************************数据库相关信息***************************/

};
