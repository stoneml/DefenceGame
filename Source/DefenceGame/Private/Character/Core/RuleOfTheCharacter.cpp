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

	//创建对应的Component
	HomingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HomingPoint"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	TraceShowCharacterInfomation = CreateDefaultSubobject<UBoxComponent>(TEXT("TraceBox"));

	//将组件绑定到根组件上
	HomingPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFirePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceShowCharacterInfomation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);



}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();


	//如果没有controller就添加一个默认的
	if (!GetController())
	{
		SpawnDefaultController();
	}

	//BeginPlay时候刷新一次血量
	UpdateUI();

}



// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


UStaticMesh* ARuleOfTheCharacter::GetDollMesh()
{
	//从当前Character的子类组建中进行查找
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
			//判断组件中的ParticleSystem是否为真，并且Emitter数量大于0
			if (ParticleComp->Template && ParticleComp->Template->Emitters.Num() > 0)
			{
				for (const UParticleEmitter* TmpEmitter : ParticleComp->Template->Emitters)
				{
					//如果他的LOD 0 是被激活的
					if (TmpEmitter->LODLevels[0]->bEnabled)
					{
						//寻找TypeMesh，然后获取Mesh
						if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(TmpEmitter->LODLevels[0]->TypeDataModule))
						{
							//最后返回DataMesh模块中的Mesh
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
			//将骨骼组件的transform设置为单位化的 （世界的和相对的都要设置）
			// FTransform MeshTransform = NewSkeletalMeshComponent->GetComponentTransform();
			//NewSkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);  //我的是正常的
			//NewSkeletalMeshComponent->SetWorldTransform(FTransform::Identity);  //我的是正常的
			
			//设置模型的相对旋转
			//(这里的旋转是需要传递一个四元，所以要进行转换)
			NewSkeletalMeshComponent->SetRelativeRotation(NewSkeletalMeshComponent->GetComponentTransform().GetRotation());

			//传入当前的骨骼模型，通过NameSpace，基本上可以等于是静态函数。
			if (UStaticMesh* NewStaticMesh =  MeshUtils::SkeletalCompToStaticMesh(GetWorld(),NewSkeletalMeshComponent))
			{
				//这部分是通过SkelatalMesh来进行获取。
				FTransform MeshTransform = NewSkeletalMeshComponent->GetComponentTransform();
				return NewStaticMesh;
			}


		}

	}


	return nullptr;
}


void ARuleOfTheCharacter::UpdateUI()
{
	//首先判定当前UI是否有效
	if (Widget)
	{
		//将UI转换为HealthUI
		if (UUI_Health* HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
		{
			HealthUI->SetTitle((GetCharacterData().Name).ToString());
			HealthUI->SetHealth(GetHealth() / GetMaxHealth());   //血量是需要获取百分比	
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

	//通过Damage获取到当前受到的伤害
	float DamageVal = Expression::CalcDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
	//GetCharacterData().Health -= (DamageVal / 10.f);
	GetCharacterData().Health -= DamageVal;

	//UKismetSystemLibrary::PrintString(this, TEXT("HP: ") + FString::SanitizeFloat(DamageVal));
	//如果自身死亡，就始终保持血量为0
	if (!IsActive())
	{
		GetCharacterData().Health = 0.f;
	}

	//每次受伤时生成一个DrawText
	if (DrawTextClass)
	{
		//传递的是需要spawn的类
		if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass,GetActorLocation(),FRotator::ZeroRotator))
		{
			FString DmgText = FString::Printf(TEXT("-%0.f"), DamageVal);
			MyValueText->SetTextBlock(DmgText, FLinearColor::Red, DamageVal / GetCharacterData().MaxHealth);
		}
	}

	//受伤之后更新UI
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
	//做一次有效性判断
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

	//调用在GameState中的 extern CharacterDataNull，这个相当于static调用。
	//return CharacterDataNULL;
	return TargetCharacterData;
}

/*
// Called to bind functionality to input
void ARuleOfTheCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}*/

