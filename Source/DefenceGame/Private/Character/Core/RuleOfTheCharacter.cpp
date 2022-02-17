// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Core/RuleOfTheCharacter.h"
#include <Components/SceneComponent.h>
#include <Components/WidgetComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/BoxComponent.h>
#include <Engine/EngineTypes.h>
#include "UObject/NoExportTypes.h"
#include "GameFramework/Pawn.h"
#include "UI/CharacterUI/UI_Health.h"
#include "../DefenceGameUtils.h"
#include "GameFramework/Actor.h"
#include "Actor/DrawText.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/TypeData/ParticleModuleTypeDataMesh.h"
#include "Particles/ParticleLODLevel.h"



// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	:bAttack(false)
{
	CurrentGUID = FGuid::NewGuid();
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//������Ӧ��Component
	HomingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HomingPoint"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	TraceShowCharacterInfomation = CreateDefaultSubobject<UBoxComponent>(TEXT("TraceBox"));

	//������󶨵��������
	HomingPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFirePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceShowCharacterInfomation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);



}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();


	//���û��controller�����һ��Ĭ�ϵ�
	if (!GetController())
	{
		SpawnDefaultController();
	}

	//BeginPlayʱ��ˢ��һ��Ѫ��
	UpdateUI();

}



// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


UStaticMesh* ARuleOfTheCharacter::GetDollMesh()
{
	//�ӵ�ǰCharacter�������齨�н��в���
	TArray<USceneComponent*> SceneComponents;
	RootComponent->GetChildrenComponents(true, SceneComponents);

	for (auto& Tmp : SceneComponents)
	{
		if (UStaticMeshComponent* NewMeshComponent = Cast<UStaticMeshComponent>(Tmp))
		{
			if (NewMeshComponent->GetStaticMesh())
			{
				return NewMeshComponent->GetStaticMesh();
			}
		}
		else if (UParticleSystemComponent* ParticleComp = Cast<UParticleSystemComponent>(Tmp))
		{
			//�ж�����е�ParticleSystem�Ƿ�Ϊ�棬����Emitter��������0
			if (ParticleComp->Template && ParticleComp->Template->Emitters.Num() > 0)
			{
				for (const UParticleEmitter* TmpEmitter : ParticleComp->Template->Emitters)
				{
					//�������LOD 0 �Ǳ������
					if (TmpEmitter->LODLevels[0]->bEnabled)
					{
						//Ѱ��TypeMesh��Ȼ���ȡMesh
						if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(TmpEmitter->LODLevels[0]->TypeDataModule))
						{
							//��󷵻�DataMeshģ���е�Mesh
							if (MyParticleDataMesh->Mesh)
							{
								return MyParticleDataMesh->Mesh;
							}				
						}
					}
				}
			}

		}
		else if (USkeletalMeshComponent* NewSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Tmp))
		{
			//�����������transform����Ϊ��λ���� ������ĺ���ԵĶ�Ҫ���ã�
			// FTransform MeshTransform = NewSkeletalMeshComponent->GetComponentTransform();
			//NewSkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);  //�ҵ���������
			//NewSkeletalMeshComponent->SetWorldTransform(FTransform::Identity);  //�ҵ���������
			
			//����ģ�͵������ת
			//(�������ת����Ҫ����һ����Ԫ������Ҫ����ת��)
			NewSkeletalMeshComponent->SetRelativeRotation(NewSkeletalMeshComponent->GetComponentTransform().GetRotation());

			//���뵱ǰ�Ĺ���ģ�ͣ�ͨ��NameSpace�������Ͽ��Ե����Ǿ�̬������
			if (UStaticMesh* NewStaticMesh =  MeshUtils::SkeletalCompToStaticMesh(GetWorld(),NewSkeletalMeshComponent))
			{
				//�ⲿ����ͨ��SkelatalMesh�����л�ȡ��
				FTransform MeshTransform = NewSkeletalMeshComponent->GetComponentTransform();
				return NewStaticMesh;
			}


		}

	}


	return nullptr;
}


void ARuleOfTheCharacter::UpdateUI()
{
	//�����ж���ǰUI�Ƿ���Ч
	if (Widget)
	{
		//��UIת��ΪHealthUI
		if (UUI_Health* HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
		{
			HealthUI->SetTitle((GetCharacterData().Name).ToString());
			HealthUI->SetHealth(GetHealth() / GetMaxHealth());   //Ѫ������Ҫ��ȡ�ٷֱ�	
		}
	}
}

EGameCharacterType::Type ARuleOfTheCharacter::GetType()
{
	return EGameCharacterType::Type::MAX;
}

float ARuleOfTheCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//ͨ��Damage��ȡ����ǰ�ܵ����˺�
	float DamageVal = Expression::CalcDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
	//GetCharacterData().Health -= (DamageVal / 10.f);
	GetCharacterData().Health -= DamageVal;

	//UKismetSystemLibrary::PrintString(this, TEXT("HP: ") + FString::SanitizeFloat(DamageVal));
	//���������������ʼ�ձ���Ѫ��Ϊ0
	if (!IsActive())
	{
		GetCharacterData().Health = 0.f;
	}

	//ÿ������ʱ����һ��DrawText
	if (DrawTextClass)
	{
		//���ݵ�����Ҫspawn����
		if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass,GetActorLocation(),FRotator::ZeroRotator))
		{
			FString DmgText = FString::Printf(TEXT("-%0.f"), DamageVal);
			MyValueText->SetTextBlock(DmgText, FLinearColor::Red, DamageVal / GetCharacterData().MaxHealth);
		}
	}

	//����֮�����UI
	UpdateUI();

	return DamageVal;
}

bool ARuleOfTheCharacter::IsDeath()
{
	//return false;
	return GetHealth() <= 0.f;
}

float ARuleOfTheCharacter::GetHealth()
{
	//��һ����Ч���ж�
	if (GetGameState())
	{
/*
		UKismetSystemLibrary::PrintString(this, TEXT("ID: ")
			+ CurrentGUID.ToString()
			+ TEXT("CurHP: ")
			+ FString::SanitizeFloat(GetGameState()->GetCharacterData(CurrentGUID).Health));*/
		return GetGameState()->GetCharacterData(CurrentGUID).Health;
	}
	return 0.f;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	if (GetGameState())
	{
/*
		UKismetSystemLibrary::PrintString(this, TEXT("ID: ")
			+ CurrentGUID.ToString()
			+ TEXT("MaxHP: ")
			+ FString::SanitizeFloat(GetGameState()->GetCharacterData(CurrentGUID).MaxHealth));*/
		return GetGameState()->GetCharacterData(CurrentGUID).MaxHealth;
	}
	return 0.f;
}

bool ARuleOfTheCharacter::IsTeam()
{
	return false;
}

FCharacterData& ARuleOfTheCharacter::GetCharacterData()
{
	if (GetGameState())
	{
		//return GetGameState()->GetCharacterData(CurrentGUID);
		TargetCharacterData = GetGameState()->GetCharacterData(CurrentGUID);
	}

	//������GameState�е� extern CharacterDataNull������൱��static���á�
	//return CharacterDataNULL;
	return TargetCharacterData;
}

/*
// Called to bind functionality to input
void ARuleOfTheCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}*/

