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

	//������
	REMOTE_MINION				UMETA(DisplayName = "Remote Minion"),
	WARRIOR_MINION				UMETA(DisplayName = "Warrior Minion"),
	BIG_MINION					UMETA(DisplayName = "Big Minion"),
	SUPER_MINION				UMETA(DisplayName = "Super Minion"),

	//������
	FIRST_CLASS_TURRETS			UMETA(DisplayName = "First Class Tower"),
	SECONDARY_DEFENSE_TOWER		UMETA(DisplayName = "Secondary Defense Tower"),
	HIGHLAND_DEFENSE_TOWER		UMETA(DisplayName = "Highland Defense Tower"),
	BASE_TOWER					UMETA(DisplayName = "Base Tower"),

	//ˮ����
	CRYSTAL_TOWER				UMETA(DisplayName = "Crystal Tower"),
	MAIN_CRYSTAL_TOWER			UMETA(DisplayName = "Main Crystal Tower"),

	//Ұ������
	WILD_MONSTER				UMETA(DisplayName = "Wild Monster"),
	WILD_BOSS_MONSTER			UMETA(DisplayName = "Wild Boss"),

	//�̵�
	BOSS_SHOP					UMETA(DisplayName = "Boss Shop"),

	//Ѫ��
	BLOOD_POOL					UMETA(DisplayName = "Blood Pool"),

	//��Ѫ��
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
	BULLET_NONE			 UMETA(DisplayName = "None"),//�������κ�Ч��

	BULLET_DIRECT_LINE	 UMETA(DisplayName = "Direct Line"),	//���ϰ�ֱ�߹���
	BULLET_LINE			 UMETA(DisplayName = "Line"),	//�Ǹ������ͣ�������ǹ�ӵ���
	BULLET_TRACK_LINE	 UMETA(DisplayName = "Track Line"),	//��������
	BULLET_TRACK_LINE_SP UMETA(DisplayName = "Track Line sp"),	//��������
	BULLET_RANGE_LINE	 UMETA(DisplayName = "Range Line"),	//��Χ�˺��������ף�
	BULLET_RANGE		 UMETA(DisplayName = "Range"),	//��Χ�˺��������Ա���
	BULLET_CHAIN		 UMETA(DisplayName = "Chain"),	//�������ͣ������˺�����;
};

UENUM(BlueprintType)
enum class ESkillEffectType :uint8
{
	EFFECT_NONE		UMETA(DisplayName = "None"),
	EFFECT_STRIKE	UMETA(DisplayName = "Strike"),		//���� (����һ�ξ��룬�ڼ��޷�����)
	EFFECT_VERTIGO  UMETA(DisplayName = "Vertigo"),		//ѣ�� (ѣ��һ��ʱ�䣬�ڼ��޷�ʹ�ü��� �޷�ʹ���ƶ���ת)
	EFFECT_SILENT	UMETA(DisplayName = "Silent"),		//��Ĭ (��Ĭһ�ξ��룬�ڼ��޷�ʹ�ü���)
	EFFECT_LIMIT	UMETA(DisplayName = "Limit"),		//��   (����һ�ξ��룬�ڼ��޷��ƶ�)
};

UENUM(BlueprintType)
enum class ERoadType :uint8
{
	ROAD_UP		UMETA(DisplayName = "UP"),
	ROAD_MID	UMETA(DisplayName = "Mid"),
	ROAD_DOWN	UMETA(DisplayName = "Down"),
};

//������Ϣ
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
