// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DefenceGameType.h"
#include "RuleOfTheBullet.generated.h"


class USplineComponent;
class UWorld;
class ARuleOfTheCharacter;



UCLASS()
class DEFENCEGAME_API ARuleOfTheBullet : public AActor
{
	GENERATED_BODY()
	
	//如果将变量写在Private里面的话可以使用这段
	// meta = (AllowPrivateAcces = "true")主要就是这一段，允许访问私有变量
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

	//写一个接触后的接口(需要被绑定的接口，需要添加UFUNCTION)
	//碰撞到的Actor、碰撞到的组件、BodyIndex、是否扫描、碰撞结果
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	//封装范围攻击
	void RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter);

protected:

	// 需要使用Ufunction才能让UE函数找到
	UFUNCTION()
	void CurrentChianAttack();


protected:

	//碰撞检测
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute")
	class USphereComponent* SphereDamage;

	//场景根组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute")
	class USceneComponent* RootBullet;

	//弹射组件ProjectileMovementComponent
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "BaseAttribute")
	class UProjectileMovementComponent* ProjectileComponent;

public:

	//子弹类型
	UPROPERTY(EditDefaultsOnly,Category = "Bullet")
	TEnumAsByte<EBulletType> BulletType;   //使用这个AsByte就能进行Byte转换了

	//伤害特效
	UPROPERTY(EditDefaultsOnly,Category = "Bullet")
	UParticleSystem* DamageParticle;
	//发射特效
	UPROPERTY(EditDefaultsOnly,Category = "Bullet")
	UParticleSystem* OpenFireParticle;

	//闪电链的攻击计数
	int32 ChainAttackCount;

/*
	UPROPERTY(EditDefaultsOnly, Category = "BulletTraceOffset")
	float TraceOffset;*/


private:

	//追踪弹使用的样条线
	UPROPERTY()
	USplineComponent* TraceSpline;

	UPROPERTY()
	float CurrentTickTime;

	//通过一个定时器来进行伤害函数周期调用
	FTimerHandle ChainAttackTimer;

};
