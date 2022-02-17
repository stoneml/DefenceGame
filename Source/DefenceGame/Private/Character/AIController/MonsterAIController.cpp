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
			//表达式自行推导捕获：当捕获列表[capture list]中不传入任何变量而是写成[=]或者[&]
			//lambda表达式会以值传递[=]或[&]引用传递的方式捕获参数，参数的捕获根据表达式中变量使用情况来推导。

			//lambda表达式
			//这里设定一个变量，但是类型是根据获取到的类型自动识别
			//lambda表达式返回值赋值   [&]引用传递	      ，传入的值,	 --> 返回类型
			auto GetRecentlyTowers = [&](const TArray<ATowers*>&MyTowers)->ATowers*
			{
				//lambda表达式函数体
				if (MyTowers.Num())
				{
					float TowerTargetDistance = 99999999.f; //初始给个很大的值
					int32 TowerIndex = INDEX_NONE;  //保存最近距离的塔ID
					FVector MyLocation = GetPawn()->GetActorLocation(); //Monster的位置

					//开始进行最近距离的遍历
					for (int32 i = 0;i<MyTowers.Num();i++)
					{
						//如果塔有效
						if (ATowers* TowerCharacter = MyTowers[i])
						{
							//首先计算距离
							FVector TowerLocation = TowerCharacter->GetActorLocation();
							FVector TmpVector = TowerLocation - MyLocation;

							//是否需要进行abs绝对值的转换
							float TowerAndMonsterDistance = TmpVector.Size();  //相当于蓝图的 vectorlength

							if (TowerAndMonsterDistance<TowerTargetDistance)
							{
								//满足条件就保存一次当前最近距离的TowerID和距离
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
				return NULL;  //如果没有返回东西就返回空
			};  //lambda 表达式结束*/

			// 	explicit TActorIterator(UWorld* InWorld, TSubclassOf<ActorType> InClass = ActorType::StaticClass(), EActorIteratorFlags InFlags = EActorIteratorFlags::OnlyActiveLevels | EActorIteratorFlags::SkipPendingKill)
			// 		: Super(InWorld, InClass, InFlags)
			// 	{
			// 		++(*this);
			// 	}

				//使用了Actor的迭代器，需要引入头文件
		for (TActorIterator<ATowers>it(GetWorld(), ATowers::StaticClass()); it; ++it)
		{
			ATowers* TheCharacter = *it;
			if (TheCharacter && TheCharacter->IsActive())  //如果塔有效且还活着
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


		//然后使用lambda获取到最近的MainTower和NorTower
		//ATowers* MainTower = GetRecentlyTowers(TargetMainTowerArray);
		//ATowers* NorTower = GetRecentlyTowers(TargetNorTowerArray);

		//获取到的目标是ARuleOfTheCharacter
		//因为这个DefenceGameUtils类使用的是Namespace，所以直接就可以用::来获取
		ATowers* MainTower = Cast<ATowers>(DefenceGameUtils::FindTargetRecently(TargetMainTowerArray, GetPawn()->GetActorLocation()));
		ATowers* NorTower = Cast<ATowers>(DefenceGameUtils::FindTargetRecently(TargetNorTowerArray, GetPawn()->GetActorLocation()));

		//有主塔就先返回主塔
		if (MainTower)
		{
			return MainTower;
		}

		//返回找到的目标
		return NorTower;
	}

	//如果不查找新目标，就返回当前目标
	return CurrentTarget.Get();

}

void AMonsterAIController::AttackTarget(ARuleOfTheCharacter* Target)
{

}
