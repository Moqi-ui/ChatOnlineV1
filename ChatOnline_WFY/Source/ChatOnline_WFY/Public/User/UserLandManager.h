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

class CHATONLINE_WFY_API FUserLandManager:public FTickableGameObject
{


public:

	virtual void Tick(float DaltaTime)override;

	virtual ETickableTickType GetTickableTickType() const override;

	virtual TStatId GetStatId() const override;


};