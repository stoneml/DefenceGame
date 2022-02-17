// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnBullet.generated.h"

/**
 * 
 */

class ARuleOfTheBullet;


UCLASS(const, hidecategories = Object, collapsecategories, Config = Game, meta = (DisplayName = "Spawn Bullet"))
class DEFENCEGAME_API UAnimNotify_SpawnBullet : public UAnimNotify
{
	GENERATED_BODY()
	

public:

	UAnimNotify_SpawnBullet();
	
	//覆写父类函数

	//返回当前Notify的名字
	virtual FString GetNotifyName_Implementation() const override;

	//通知的内容
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


public:

	//创建一个对应选择的子弹类型(使用TsubofClass是可以让在蓝图中进行添加)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	TSubclassOf<ARuleOfTheBullet> BulletClass;


	//如果在编辑器状态下，那么就使用一个SocketName，然后查找对应骨骼
#if WITH_EDITOR
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AnimNotify",meta = (ExposeOnSpawn = true))
	FName InSocketName;
#endif

};
