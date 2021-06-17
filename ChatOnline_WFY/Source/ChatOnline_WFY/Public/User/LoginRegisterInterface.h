// Fill out your copyright notice in the Description page of Project Settings.

/*********************************************************
* @copyright		2020 - 2021, DreamMaster.Co, Ltd.All right reserved
*
* @author			imrcao
* @date				2021/4/8-21:09
* @brief			�û���¼�ӿ�
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

	/**����������ʾ�����							by moqi 20190925*/
	UTextBlock* pMessageLoginPromptWord;

	/**�û���¼���湤��							by moqi 20190925*/
	FUserLandManager* UserLandManager;

	/**�û�������ֻ���							by moqi 201909026*/
	FString UserInputNumber;
	/**�û����������								by moqi 201909026*/
	FString UserInputPassword;
	/**�û��ڶ������������						by moqi 201909026*/
	FString SecondPassword;
	/**�û��������֤��							by moqi 201909026*/
	FString UserInputVerification;
	/**�û����������								by moqi 201909026*/
	FString UserInputName;
	/**������¼�ֻ��Ÿ�ʽ�Ƿ���ȷ					by moqi 20190926*/
	bool IsPhoneNumberFormat = false;
	/**������¼�����ʽ�Ƿ���ȷ					by moqi 20190926*/
	bool IsPasswordFormat = false;
	/**������¼��֤���ʽ�Ƿ���ȷ					by moqi 20190926*/
	bool IsVerificationCodeFormat = false;
	/**������¼�û�����ʽ�Ƿ���ȷ					by moqi 20190926*/
	bool IsUserNameFormat = false;
	/**������¼�û���������������Ƿ�һ��			by moqi 20190926*/
	bool IsPasswordEquality = false;

	FTimerHandle MyTimeHandle;

public:

	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void Print_F(FString InputStr);

	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void init();

	/**��ʾ�򴴽�һ���ؼ�								by imrcao 20210422
	*@param							SelfWidget		����ؼ�
	*@param							MyUserWidget	ָ��Ҫ�����Ŀؼ�
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void ShowOrCreateOneWidget(UWidget* SelfWidget, TSubclassOf<UUserWidget> MyUserWidget);


	/**���û��������ֻ��ź󣬸���������з���			by moqi 20190925
	*  ����������ݲ��淶������������Ӧ����ʾ
	*@param							PhoneNumber		�û�������ֻ���
	*@param							IsLoginInterface������¼�ǲ��ǵ�¼����
	@RETURN											�û�����ĸ�ʽ�Ƿ���ȷ
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnPhoneNumberCommit(FText PhoneNumber, bool IsLoginInterface);

	/**���û�������������ж������Ƿ���Ϲ���			by moqi 20190925
	*@param							Password		�û����������
	*RETURN											����������Ƿ���Ϲ淶
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnInputPasswordCommit(FText Password);

	/**���û��������û������ж��û����Ƿ���Ϲ���		bu moqi 20190925
	*@param							UserName		�û�������û���
	*RETURN											������û����Ƿ���Ϲ淶
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnInputUserNameCommit(FText UserName);

	/**�������ȡ��֤�밴ť��ִ��						bu moqi 20190926
	*RETURN											�Ƿ��ȡ�ɹ�
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		bool OnClickGetVerificationButton();

	/**����˳���¼��ť								by moqi 20190930*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void OnClickExistLoginButton();


	/*****************************�˺������¼������õķ���******************************/

	/**���û������¼��ťʱִ��						by moqi 20190925
	*RETURN											�Ƿ��¼�ɹ�
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickPasswordLoginButton();

	/**���ñ���TheButtonIsEnable,���ݴ���İ�ť���Ͳ�ͬ��ִ�в�ͬ�߼�	by moqi 20190926
	*@param							ButtonType						��ť����
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetTheButtonIsEnable(FString ButtonType);

	/**���á��������롱��ť�Ƿ��ɫ����									by moqi 20191018
	*@param							ButtonType						��ť����
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetForgetPasswordColor();

	/*****************************��֤���¼������õķ���******************************/

	/**���û������֤���¼��ťʱִ��						by moqi 20190925
	*RETURN												�Ƿ��¼�ɹ�
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickCodeLoginButton();


	/*****************************ע�������õķ���******************************/

	/**���û����ע�ᰴťʱִ��							by moqi 20190925
	*RETURN												�Ƿ�ע��ɹ�
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickRegisterButton();

	/***************************** �޸����������õķ���******************************/

	/**�����޸�������棬����ǰ�û����ֻ���Ĭ������������Ҳ��ܱ༭				by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void OnModifyPasswordWidget();

	/**�ж����������Ƿ�һ��								by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool JudgePasswordEquality();

	/**���û��ڶ��������������							by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnUserSecondCommitPassword(FText SecondPassword);

	/**���ȷ���޸İ�ťִ��								by moqi 20190930
	*RETURN												�Ƿ��޸ĳɹ�
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool OnClickConfirmModifyButton();

	/**�����ֻ���ʽ���û�ȡ��֤�밴ť����ɫ�Ͱ�ť�Ƿ��ܵ��	by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetCodeButtonColorAndActive();

	/**���û�ȡ��֤�밴ťΪ���ɵ��״̬						by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetCodeButtonCanNotClick();

	/**���û�ȡ��֤�밴ťΪ�ɵ��״̬					by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void SetCodeButtonCanClick();

	/**��õ�ǰ��¼�û����û�����ʾ��UI						by moqi 20190930
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		void ShowCurrentUserName();

	/**��õ�ǰ�Ƿ����û���¼									by moqi 20191018
	*/
	UFUNCTION(BlueprintCallAble, Category = "UIEvent")
		bool GetIsInUserLand();



public:


	/**��¼��ť���Ƿ�ɵ��								by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool TheButtonIsEnable = false;

	/**��¼ע�ᰴť����ɫ									by moqi 20190926*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FLinearColor TheButtonBGColor = FLinearColor(FColor(0, 0, 0, 1));

	/**��ʾ����											by moqi 20190926*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText PromptWords;

	/**��ʾ����״̬										by moqi 20190926*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TEnumAsByte<ESlateVisibility> PromptWordsState;

	/**��ǰ�û����ֻ���									by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText CurrentUserPhoneNumber;

	/**��ȡ��֤�밴ť�ı�����ɫ							by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FLinearColor CodeButtonBGColor = FLinearColor(FColor(0, 0, 0, 1));

	/**��ȡ��֤�밴ť���Ƿ�ɵ��							by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool CodeButtonIsEnable = false;

	/**��ȡ��ȡ��ǰ��¼�û����û���						by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText CurrentUserName;

	/**�������밴ť���Ƿ�ɵ�����ֻ���ע�����δ��¼����Ե���������룩	by moqi 20191017*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool ForgetPasswordButton = false;

	/**����������ɫ										by moqi 20190930*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FLinearColor ForgetTextColor = FLinearColor(FColor(0, 0, 0, 0.3));


public:

	//���Ժ���

	UFUNCTION(BlueprintCallable, Category = "UISQLtest")
		bool QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug);


	UFUNCTION(BlueprintCallable, Category = "UISQLtest")
		bool InsertTableDatasTest();



private:


	//FUserLandManager* UserLandManager;

	TSharedPtr<FSimpleMysqlLink> Link;

	/******************************���ݿ������Ϣ***************************/

	FString InUser = "root";

	FString InHost = "127.0.0.1";

	FString InPawd = "Mrcao";

	FString InDB = "wfy_database";

	uint32  InPort = 3306;

	FString Unix_Socket = TEXT("\0");

	TArray<ESimpleClientFlags> InClientFlag = TArray<ESimpleClientFlags>();

	/******************************���ݿ������Ϣ***************************/

};
