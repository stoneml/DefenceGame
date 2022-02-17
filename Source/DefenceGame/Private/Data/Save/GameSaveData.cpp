// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Save/GameSaveData.h"


FBuildingTower::FBuildingTower()
{
	InitSaveData();
}

void FBuildingTower::InitSaveData()
{
	//��ʼ������Ϣ
	TowerID = INDEX_NONE;
	NeedGold = INDEX_NONE;
	TowersPerpareBuildingNumber = 0;
	TowersConstructionNumber = 0;
	MaxConstructionTowersCD = 0.f;
	CurrentConstrictionTowersCD = 0.f;
	Icon = nullptr;
	bDragICO = false;
	bLockCD = false;
	bCallUpdateTowerInfo = false;
}

float FBuildingTower::GetTowerConstructionTimePercentage()
{
	//�����ж������CD��ֵ�Ƿ��Ǵ���0�ģ�����ǵĻ��ͽ��аٷֱȼ���
	return MaxConstructionTowersCD > 0 ? CurrentConstrictionTowersCD / MaxConstructionTowersCD : 0.f;
}

bool FBuildingTower::IsValid()
{
	return TowerID != INDEX_NONE ? true : false;
}

void FBuildingTower::ResetCD()
{
	CurrentConstrictionTowersCD = MaxConstructionTowersCD;
}
