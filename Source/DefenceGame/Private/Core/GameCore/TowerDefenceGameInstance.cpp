// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameInstance.h"
#include <SimpleScreenLoading.h>
#include <Modules/ModuleManager.h>

void UTowerDefenceGameInstance::Init()
{
	Super::Init();

	//�ڳ�ʼ����ʱ�򣬴���һ��ģ�����Ӧ�á�
	FSimpleScreenLoadingModule &SimpleScreenLoadingModule = FModuleManager::LoadModuleChecked<FSimpleScreenLoadingModule>("SimpleScreenLoading");

	//������ɺ����ģ���еĺ���ʹ��
	//�������ʱ����ʹ��ָ���ͷ�����ҵ��������������loadmodulechecked���ص���ջ�ڴ�Ķ���������ָ��
	SimpleScreenLoadingModule.SetupScreenLoading();

}
