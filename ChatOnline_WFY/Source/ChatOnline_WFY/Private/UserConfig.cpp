// Fill out your copyright notice in the Description page of Project Settings.

#include "UserConfig.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"

const FString UserInfoSection = TEXT("UserInfoSection");

void UserConfig::SetAppID(const std::string& appID) {
	GConfig->SetString(*UserInfoSection, TEXT("AppID"), UTF8_TO_TCHAR(appID.c_str()), GGameIni);
	GConfig->Flush(false, GGameIni);
}
//
// APP ID��APP KEY, ���ܻ᲻�����޸���˲���֧�ֲ�Ʒʹ��, ������������.
// �����Ʒʹ��������ĵ����� GMEӦ��,  https://console.cloud.tencent.com/gamegme
// ͬʱ�滻�˴�(����һ���滻)
std::string UserConfig::GetAppID() {
	FString appID;
	GConfig->GetString(*UserInfoSection, TEXT("AppID"), appID, GGameIni);
	if (appID.IsEmpty())
	{
		appID = "1400452190";//AppID To Replace Here https://cloud.tencent.com/document/product/607/10782;
	}
	return TCHAR_TO_UTF8(*appID);
}
void UserConfig::SetAppKey(const std::string& appKey) {
	GConfig->SetString(*UserInfoSection, TEXT("AppKey"), UTF8_TO_TCHAR(appKey.c_str()), GGameIni);
	GConfig->Flush(false, GGameIni);
}
std::string UserConfig::GetAppKey() {
	FString appKey;
	GConfig->GetString(*UserInfoSection, TEXT("AppKey"), appKey, GGameIni);
	if (appKey.IsEmpty())
	{
		appKey = "U8fTpuA3H0tl4PyI"; // AppKey To Replace Here https ://cloud.tencent.com/document/product/607/10782;
	}
	return TCHAR_TO_UTF8(*appKey);
}

void UserConfig::SetRoomID(const std::string& roomID) {
	GConfig->SetString(*UserInfoSection, TEXT("RoomID"), UTF8_TO_TCHAR(roomID.c_str()), GGameIni);
	GConfig->Flush(false, GGameIni);
}
std::string UserConfig::GetRoomID() {
	FString roomID;
	GConfig->GetString(*UserInfoSection, TEXT("RoomID"), roomID, GGameIni);
	if (roomID.IsEmpty())
	{
		roomID = "201808";
	}
	return TCHAR_TO_UTF8(*roomID);

}