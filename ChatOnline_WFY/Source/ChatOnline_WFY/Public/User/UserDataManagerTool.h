
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

class FUserDataManagerTool
{
public:

	FUserDataManagerTool();

	~FUserDataManagerTool();

	void setSqlLink(TSharedPtr<FSimpleMysqlLink> Link_);

public:

	bool QueryLinkResultTest1();

private:

	TSharedPtr<FSimpleMysqlLink> Link;

};