// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleNetChannelType.h"
#include "MobyGameType.generated.h"

UENUM()
enum class ETeamType : uint8
{
	TEAM_RED,
	TEAM_BLUE,
	TEAM_NEUTRAL,
};

UENUM()
enum class ECharacterType : uint8
{
	PLAYER						UMETA(DisplayName = "Player"),

	//兵类型
	REMOTE_MINION				UMETA(DisplayName = "Remote Minion"),
	WARRIOR_MINION				UMETA(DisplayName = "Warrior Minion"),
	BIG_MINION					UMETA(DisplayName = "Big Minion"),
	SUPER_MINION				UMETA(DisplayName = "Super Minion"),

	//塔类型
	FIRST_CLASS_TURRETS			UMETA(DisplayName = "First Class Tower"),
	SECONDARY_DEFENSE_TOWER		UMETA(DisplayName = "Secondary Defense Tower"),
	HIGHLAND_DEFENSE_TOWER		UMETA(DisplayName = "Highland Defense Tower"),
	BASE_TOWER					UMETA(DisplayName = "Base Tower"),

	//水晶塔
	CRYSTAL_TOWER				UMETA(DisplayName = "Crystal Tower"),
	MAIN_CRYSTAL_TOWER			UMETA(DisplayName = "Main Crystal Tower"),

	//野怪类型
	WILD_MONSTER				UMETA(DisplayName = "Wild Monster"),
	WILD_BOSS_MONSTER			UMETA(DisplayName = "Wild Boss"),

	//商店
	BOSS_SHOP					UMETA(DisplayName = "Boss Shop"),

	//血池
	BLOOD_POOL					UMETA(DisplayName = "Blood Pool"),

	//眼血池
	EYE_POOL					UMETA(DisplayName = "Eye Pool"),
};

UENUM(BlueprintType)
enum class EBulletType :uint8
{
	BULLET_ATTACK  UMETA(DisplayName = "Attack"),
	BULLET_DEFENCE UMETA(DisplayName = "Defence"),
	BULLET_GAIN    UMETA(DisplayName = "Gain"),
};

UENUM(BlueprintType)
enum class EBulletAttackType :uint8
{
	BULLET_NONE			 UMETA(DisplayName = "None"),//不产生任何效果

	BULLET_DIRECT_LINE	 UMETA(DisplayName = "Direct Line"),	//无障碍直线攻击
	BULLET_LINE			 UMETA(DisplayName = "Line"),	//非跟踪类型，类似手枪子弹；
	BULLET_TRACK_LINE	 UMETA(DisplayName = "Track Line"),	//跟踪类型
	BULLET_TRACK_LINE_SP UMETA(DisplayName = "Track Line sp"),	//跟踪类型
	BULLET_RANGE_LINE	 UMETA(DisplayName = "Range Line"),	//范围伤害，丢手雷；
	BULLET_RANGE		 UMETA(DisplayName = "Range"),	//范围伤害，类似自爆；
	BULLET_CHAIN		 UMETA(DisplayName = "Chain"),	//链条类型，持续伤害类型;
};

UENUM(BlueprintType)
enum class ESkillEffectType :uint8
{
	EFFECT_NONE		UMETA(DisplayName = "None"),
	EFFECT_STRIKE	UMETA(DisplayName = "Strike"),		//击飞 (击飞一段距离，期间无法动弹)
	EFFECT_VERTIGO  UMETA(DisplayName = "Vertigo"),		//眩晕 (眩晕一段时间，期间无法使用技能 无法使用移动旋转)
	EFFECT_SILENT	UMETA(DisplayName = "Silent"),		//沉默 (沉默一段距离，期间无法使用技能)
	EFFECT_LIMIT	UMETA(DisplayName = "Limit"),		//控   (击飞一段距离，期间无法移动)
};

UENUM(BlueprintType)
enum class ERoadType :uint8
{
	ROAD_UP		UMETA(DisplayName = "UP"),
	ROAD_MID	UMETA(DisplayName = "Mid"),
	ROAD_DOWN	UMETA(DisplayName = "Down"),
};

//网关信息
struct FGateInfo
{
	FGateInfo()
	{
		FMemory::Memset(Name, 0, 20);
	}

	FGateInfo(const FSimpleAddr& InAddr, char* InName, int32 NameLen)
		:Addr(InAddr)
	{
		FMemory::Memset(Name, 0, 20);
		FMemory::Memcpy(Name, InName, NameLen);
	}

	FSimpleAddr Addr;
	char Name[20];
};
