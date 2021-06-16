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


public:

	//���Ժ���

	UFUNCTION(BlueprintCallable, Category = "UISQLtest")
		bool QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug);

private:


	FUserLandManager* userLandManger;

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
