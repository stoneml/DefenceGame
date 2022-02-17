// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DefenceGameType.h"
#include "RuleOfTheBullet.generated.h"


class USplineComponent;


#define PI 3.1415926


UCLASS()
class DEFENCEGAME_API ARuleOfTheBullet : public AActor
{
	GENERATED_BODY()
	
	//���������д��Private����Ļ�����ʹ�����
	// meta = (AllowPrivateAcces = "true")��Ҫ������һ�Σ��������˽�б���
	//UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute",meta = (AllowPrivateAcces = "true"))


public:	
	// Sets default values for this actor's properties
	ARuleOfTheBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//дһ���Ӵ���Ľӿ�(��Ҫ���󶨵Ľӿڣ���Ҫ���UFUNCTION)
	//��ײ����Actor����ײ���������BodyIndex���Ƿ�ɨ�衢��ײ���
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	//��װ��Χ����
	void RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter);


protected:

	// ��Ҫʹ��Ufunction������UE�����ҵ�
	UFUNCTION()
	void CurrentChianAttack();


protected:

	//��ײ���
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute")
	class USphereComponent* SphereDamage;

	//���������
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute")
	class USceneComponent* RootBullet;

	//�������ProjectileMovementComponent
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute")
	class UProjectileMovementComponent* ProjectileComponent;

public:

	//�ӵ�����
	UPROPERTY(EditDefaultsOnly,Category = "Bullet")
	TEnumAsByte<EBulletType> BulletType;   //ʹ�����AsByte���ܽ���Byteת����

	//�˺���Ч
	UPROPERTY(EditDefaultsOnly,Category = "Bullet")
	UParticleSystem* DamageParticle;
	//������Ч
	UPROPERTY(EditDefaultsOnly,Category = "Bullet")
	UParticleSystem* OpenFireParticle;

	//�������Ĺ�������
	int32 ChainAttackCount;

/*
	UPROPERTY(EditDefaultsOnly, Category = "BulletTraceOffset")
	float TraceOffset;*/


private:

	//׷�ٵ�ʹ�õ�������
	UPROPERTY()
	USplineComponent* TraceSpline;

	UPROPERTY()
	float CurrentTickTime;

	//ͨ��һ����ʱ���������˺��������ڵ���
	FTimerHandle ChainAttackTimer;

	

};
