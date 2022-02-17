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
	
	//������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ParticleMesh;

	//������Χģ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshBuilding;

	//��ʱ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UDestructibleComponent* DestructibleMeshBuilding;


public:

	ATowers();

	//�̳и���ӿ�
	virtual EGameCharacterType::Type GetType();

	//�趨���Ķ���Ϊtrue
	virtual bool IsTeam() { return true; }

	//���һ��Tower����ת�������ṩ����ͼ���ж�ȡ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute");
	FRotator TowerRotaotor;



protected:

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	
};
