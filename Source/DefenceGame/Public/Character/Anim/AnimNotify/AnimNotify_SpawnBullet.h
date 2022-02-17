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
	
	//��д���ຯ��

	//���ص�ǰNotify������
	virtual FString GetNotifyName_Implementation() const override;

	//֪ͨ������
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


public:

	//����һ����Ӧѡ����ӵ�����(ʹ��TsubofClass�ǿ���������ͼ�н������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	TSubclassOf<ARuleOfTheBullet> BulletClass;


	//����ڱ༭��״̬�£���ô��ʹ��һ��SocketName��Ȼ����Ҷ�Ӧ����
#if WITH_EDITOR
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AnimNotify",meta = (ExposeOnSpawn = true))
	FName InSocketName;
#endif

};
