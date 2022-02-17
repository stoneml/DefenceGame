// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/MonsterAIController.h"
#include <Character/CharacterCore/Towers.h>
#include <EngineUtils.h>
#include "../DefenceGameUtils.h"
//#include <Kismet/GameplayStatics.h>



AActor* AMonsterAIController::FindTarget()
{

	if (!CurrentTarget.IsValid()||!CurrentTarget->IsActive())
	{
		TArray<ARuleOfTheCharacter*>TargetMainTowerArray;
		TArray<ARuleOfTheCharacter*>TargetNorTowerArray;

		/*
			//���ʽ�����Ƶ����񣺵������б�[capture list]�в������κα�������д��[=]����[&]
			//lambda���ʽ����ֵ����[=]��[&]���ô��ݵķ�ʽ��������������Ĳ�����ݱ��ʽ�б���ʹ��������Ƶ���

			//lambda���ʽ
			//�����趨һ�����������������Ǹ��ݻ�ȡ���������Զ�ʶ��
			//lambda���ʽ����ֵ��ֵ   [&]���ô���	      �������ֵ,	 --> ��������
			auto GetRecentlyTowers = [&](const TArray<ATowers*>&MyTowers)->ATowers*
			{
				//lambda���ʽ������
				if (MyTowers.Num())
				{
					float TowerTargetDistance = 99999999.f; //��ʼ�����ܴ��ֵ
					int32 TowerIndex = INDEX_NONE;  //��������������ID
					FVector MyLocation = GetPawn()->GetActorLocation(); //Monster��λ��

					//��ʼ�����������ı���
					for (int32 i = 0;i<MyTowers.Num();i++)
					{
						//�������Ч
						if (ATowers* TowerCharacter = MyTowers[i])
						{
							//���ȼ������
							FVector TowerLocation = TowerCharacter->GetActorLocation();
							FVector TmpVector = TowerLocation - MyLocation;

							//�Ƿ���Ҫ����abs����ֵ��ת��
							float TowerAndMonsterDistance = TmpVector.Size();  //�൱����ͼ�� vectorlength

							if (TowerAndMonsterDistance<TowerTargetDistance)
							{
								//���������ͱ���һ�ε�ǰ��������TowerID�;���
								TowerIndex = i;
								TowerTargetDistance = TowerAndMonsterDistance;
							}

							if (TowerIndex != INDEX_NONE)
							{
								return MyTowers[TowerIndex];
							}
						}
					}
				}
				return NULL;  //���û�з��ض����ͷ��ؿ�
			};  //lambda ���ʽ����*/

			// 	explicit TActorIterator(UWorld* InWorld, TSubclassOf<ActorType> InClass = ActorType::StaticClass(), EActorIteratorFlags InFlags = EActorIteratorFlags::OnlyActiveLevels | EActorIteratorFlags::SkipPendingKill)
			// 		: Super(InWorld, InClass, InFlags)
			// 	{
			// 		++(*this);
			// 	}

				//ʹ����Actor�ĵ���������Ҫ����ͷ�ļ�
		for (TActorIterator<ATowers>it(GetWorld(), ATowers::StaticClass()); it; ++it)
		{
			ATowers* TheCharacter = *it;
			if (TheCharacter && TheCharacter->IsActive())  //�������Ч�һ�����
			{
				if (TheCharacter->GetType() == EGameCharacterType::Type::MAIN_TOWER)
				{
					TargetMainTowerArray.Add(TheCharacter);
				}
				else if (TheCharacter->GetType() == EGameCharacterType::Type::TOWER)
				{
					TargetNorTowerArray.Add(TheCharacter);
				}
			}
		}


		//Ȼ��ʹ��lambda��ȡ�������MainTower��NorTower
		//ATowers* MainTower = GetRecentlyTowers(TargetMainTowerArray);
		//ATowers* NorTower = GetRecentlyTowers(TargetNorTowerArray);

		//��ȡ����Ŀ����ARuleOfTheCharacter
		//��Ϊ���DefenceGameUtils��ʹ�õ���Namespace������ֱ�ӾͿ�����::����ȡ
		ATowers* MainTower = Cast<ATowers>(DefenceGameUtils::FindTargetRecently(TargetMainTowerArray, GetPawn()->GetActorLocation()));
		ATowers* NorTower = Cast<ATowers>(DefenceGameUtils::FindTargetRecently(TargetNorTowerArray, GetPawn()->GetActorLocation()));

		//���������ȷ�������
		if (MainTower)
		{
			return MainTower;
		}

		//�����ҵ���Ŀ��
		return NorTower;
	}

	//�����������Ŀ�꣬�ͷ��ص�ǰĿ��
	return CurrentTarget.Get();

}

void AMonsterAIController::AttackTarget(ARuleOfTheCharacter* Target)
{

}
