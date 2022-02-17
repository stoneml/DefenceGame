// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCore/Towers.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/StaticMeshComponent.h>
//#include "../Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleComponent.h"

ATowers::ATowers()
{

	ParticleMesh = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleMesh"));
	StaticMeshBuilding = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RangeBuilding"));
	//DestructibleMeshBuilding = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Substitute"));

	//ʹ��::��ʱ����Ҫ������()
	ParticleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//DestructibleMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

EGameCharacterType::Type ATowers::GetType()
{
	return EGameCharacterType::Type::TOWER;
}

float ATowers::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	
	return 0;
}
