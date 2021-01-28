// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>

/**
 *
 */
class CHATONLINE_WFY_API UserConfig
{
public:
	static void SetAppID(const std::string& appID);
	static std::string GetAppID();
	static void SetAppKey(const std::string& appKey);
	static std::string GetAppKey();
	static void SetRoomID(const std::string& roomID);
	static std::string GetRoomID();
};