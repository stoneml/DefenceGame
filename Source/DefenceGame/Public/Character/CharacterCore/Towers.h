// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Towers.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ATowers : public ARuleOfTheCharacter
{
	GENERATED_BODY()

private:
	
	//粒子塔
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ParticleMesh;

	//建筑范围模型
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshBuilding;

	//损坏时的塔
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UDestructibleComponent* DestructibleMeshBuilding;


public:

	ATowers();

	//继承父类接口
	virtual EGameCharacterType::Type GetType();

	//设定塔的队伍为true
	virtual bool IsTeam() { return true; }

	//添加一个Tower的旋转变量，提供给蓝图进行读取
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute");
	FRotator TowerRotaotor;



protected:

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	
};
