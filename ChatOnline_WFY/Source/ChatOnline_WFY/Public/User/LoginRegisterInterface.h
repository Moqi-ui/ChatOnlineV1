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

	/**显示或创建一个控件								by imrcao 20210422
	*@param							SelfWidget		自身控件
	*@param							MyUserWidget	指定要创建的控件
	*/
	UFUNCTION(BlueprintCallable, Category = "UIEvent")
		void ShowOrCreateOneWidget(UWidget* SelfWidget, TSubclassOf<UUserWidget> MyUserWidget);


public:

	//测试函数

	UFUNCTION(BlueprintCallable, Category = "UISQLtest")
		bool QueryLinkResultTest(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FSimpleMysqlDebugResult& Debug);

private:


	FUserLandManager* userLandManger;

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
