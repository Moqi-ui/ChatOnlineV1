#include "UserDataType.h"

FDMUserData::FDMUserData()
{

}

FDMUserData::FDMUserData(int userID_, FString userName_, FString userPhoneNumber_, FString userPower_, FString userAvatar_, FDateTime userRegisterTime_)
	:userID(userID_), userName(userName_), userPhoneNumber(userPhoneNumber_), userPower(userPower_), userAvatar(userAvatar_), userRegisterTime(userRegisterTime_)
{

}