// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bullet/RuleOfTheBullet.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Character/Core/RuleOfTheAIController.h"
#include "EngineUtils.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ARuleOfTheBullet::ARuleOfTheBullet()
{
	ChainAttackCount = 3;
	TraceSpline = nullptr;
	CurrentTickTime = 0.f;
	//TraceOffset = 0.f

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�������
	SphereDamage = CreateDefaultSubobject<USphereComponent>(TEXT("BulletDamage"));
	RootBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRootBullet"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectileComponent"));

	//�����
	RootComponent = RootBullet;
	SphereDamage->AttachToComponent(RootBullet, FAttachmentTransformRules::KeepRelativeTransform);

	//���õ�������ĳ�ʼ״̬
	ProjectileComponent->MaxSpeed = 2000.f;
	ProjectileComponent->InitialSpeed = 1600.f;
	ProjectileComponent->ProjectileGravityScale = 0.f;  //��������Ϊ0
	ProjectileComponent->UpdatedComponent = SphereDamage;  //Ч��Ӱ�쵽��Ӧ�����

	BulletType = EBulletType::BULLET_DIRECT_LINE;

	//�����ӵ����ʱ��
	InitialLifeSpan = 4.f;

}

// Called when the game starts or when spawned
void ARuleOfTheBullet::BeginPlay()
{
	Super::BeginPlay();

	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter* TargetCharacter = Cast<ARuleOfTheCharacter>(InstigatorController->CurrentTarget.Get()))
			{

				//ͨ�����ͳ�ʼ���ӵ�״̬
				switch (BulletType)
				{
				case EBulletType::BULLET_DIRECT_LINE:
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					break;
				case EBulletType::BULLET_LINE:
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					break;
				case EBulletType::BULLET_TRACK_LINE:
				{

					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					ProjectileComponent->bIsHomingProjectile = true;
					ProjectileComponent->bRotationFollowsVelocity = true;

					//���Ȼ�ȡʩ���ߣ������ӵ���Actor��
					//ͨ����ǰ�����controller��ȡ����Controller��Ȼ���ȡ��Ŀ��
					//��ȡ��controller�е�target�����target����ָ�룬��Ҫʹ��.Get() ������ת��Ϊ��ָ�룩
					//�����ӵ��ĵ������ã�HomingAccelerationMagnitude����ǰ׷��Ŀ��ļ��ٶȴ�С��������Ϊ4000
					//���HomingTargetComponentΪĿ�����ϵ�HomingTarget

					ProjectileComponent->HomingAccelerationMagnitude = 4000.f;
					ProjectileComponent->HomingTargetComponent = TargetCharacter->GetHomingPoint();

				}
				break;
				case EBulletType::BULLET_TRACK_LINE_SP:
				{
					//������Ҫ�ڷ���ʱ������Ч��
					ProjectileComponent->StopMovementImmediately();
					UGameplayStatics::SpawnEmitterAtLocation(this, OpenFireParticle, GetActorLocation());
					TraceSpline = NewObject<USplineComponent>(this, TEXT("TraceSpline"));
					TraceSpline->RegisterComponent();

					//�� ����Spline��Ȼ���һ�����λ�����ڵ�����λ��
					//�� ��������˭�ͼ���˭���õ��ľ����յ��λ�á���ǰ��A����B��
					//�� Ȼ�����ø߶�
					//�� //�����Y������ǿ����Զ���ģ����ӵ���������Ť����
					//�� �ղż����λ��������ø���һ��
					//�� ���������һ����λ����������λ���Ƿ��ڵ��˵�λ��(λ�ÿռ�ΪLocal)��
					//�� ��Ϊ�ǰ���Spline�������ƶ�����������ֱ�Ӿ�ֹͣ��ProjectileMovement���ƶ�������

					TraceSpline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::Local);

					FVector TraceDistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
					
					FVector CurvePosition = (TraceDistanceVector / 2) + TargetCharacter->GetActorLocation();
					//CurvePosition.Y = TraceOffset;
					CurvePosition.Z = (TraceDistanceVector.Size() / 2) * 0.7f;
					TraceSpline->SetLocationAtSplinePoint(1, CurvePosition, ESplineCoordinateSpace::Local);
					TraceSpline->AddSplinePoint(TargetCharacter->GetActorLocation(),ESplineCoordinateSpace::Local);

					break;
				}
				case EBulletType::BULLET_RANGE_LINE:
				{
					ProjectileComponent->StopMovementImmediately();

					//���Ȼ�ȡʩ����
					//��ȡʩ���ߵ�Controller Ϊ�˻�ȡ���е�Target (Target��Ҫ��ȡBaseController����ȡ��
					//��ȡTarget��ת��ΪARuleOfCharacter
					//����ProjectileMovement��������
					//�����ڵ���Target�ľ��롣
					//ͨ�� t = S/v �����ʱ�� ����ά�ģ�
					//ͨ�� gt����õ�Y���ֵ��
					//ͨ����ʼ�ٶ� v * t �����X����ĳ��ȡ�
					//ͨ�����ɶ������������ǵ� v���ٶȡ�
					//ͨ����ʽ���з��仡��cos����(�����ң���(��Ҫ���� c = PI*0.1��
					//Ȼ�󽫻���תΪ�Ƕ� = ���� * ��180 / PI��
					//��������ڵ���תֵ
					//��Porjectile�����趨һ���ٶȣ�X ����������* �����ʼ�ٶ�

					ProjectileComponent->ProjectileGravityScale = 1.f;  //��������
				/*	FVector DistanceVector = Target->GetActorLocation() - GetActorLocation();

					float InTime = DistanceVector.Size() / (ProjectileComponent->InitialSpeed);
					float Y = ProjectileComponent->GetGravityZ() * InTime;	//Y����߶�
					float X = ProjectileComponent->InitialSpeed * InTime;  //X���򳤶�

					float V = FMath::Sqrt(X * X + Y * Y);  //���ɶ������
					float CosRadian = FMath::Acos(DistanceVector.Size() / (V * (InTime * (PI * 0.1f))));
					FRotator Rot = GetActorRotation();
					Rot.Pitch = CosRadian * (180 / PI);
					SetActorRotation(Rot);*/

					//����˺������⡣
					FVector DistanceVector = TargetCharacter->GetActorLocation() - GetActorLocation();
					float InTime = DistanceVector.Size() / ProjectileComponent->InitialSpeed;

					// tan �Ա����ڱߵı�ֵ
					float TanRadian = FMath::Atan(((ProjectileComponent->GetGravityZ() * (InTime)) * (PI * 0.1f)) / (DistanceVector.Size() / 2));
					FRotator Rot = GetActorRotation();
					//Rot.Pitch = TanRadian*(180/PI);
					Rot.Pitch = TanRadian;
					SetActorRotation(Rot);

					//�����趨�ٶ�
					ProjectileComponent->SetVelocityInLocalSpace(FVector(1.f, 0.f, 0.f) * ProjectileComponent->InitialSpeed);
				}
				break;
				case EBulletType::BULLET_RANGE:

					//���Ȼ��ʩ����
					//ֹͣProjectile�ƶ�
					//ʹ�õ�������ȡ�������е�ARuleOfCharacter
					//����ɸѡ���жϵ�ǰĿ���Ƿ����תΪARuleOfCharacter
					//������룬�������С��1400�ͷ���
					//�ж�Ŀ����Ӫ��������ѷ��Ͳ�����˺�
					//���Ǿʹ�����ըЧ���Լ�����˺���

					SphereDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					//���÷�Χ�˺�������
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));

					/*
							if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
							{
								ProjectileComponent->StopMovementImmediately();
								TArray<AActor*>IgnoreActors; //���Ե�Ŀ��
								//TArray<ARuleOfTheCharacter*>TargetCharacter;  //����Ŀ��
								for (TActorIterator<ARuleOfTheCharacter> it(GetWorld(),ARuleOfTheCharacter::StaticClass());it; ++it)
								{
									if (ARuleOfTheCharacter* TheCharacter = *it)  //�ж�Ŀ���Ƿ���ת���ɶ�Ӧ��Character
									{
										//��Ŀ�꿪����ж��˺���Χ�ڵ�����Ŀ�����ڵ�����ľ���
										FVector TargetDistance = TheCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
										if (TargetDistance.Size()<=1400.f)
										{
											if (TheCharacter->IsTeam() == InstigatorCharacter->IsTeam())
											{
												IgnoreActors.Add(TheCharacter);
											}
											else
											{
												//����һ���ӵľ͹�����
												UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, TheCharacter->GetActorLocation());
												//TargetCharacter.Add(TheCharacter);
											}
										}
									}
								}

								//��Χ����
								UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), 100.f, 10.f, GetActorLocation(), 400.f, 1000.f, 1.f, UDamageType::StaticClass(), IgnoreActors, InstigatorCharacter);

							}*/
				break;
				case EBulletType::BULLET_CHAIN:
				{

					ProjectileComponent->StopMovementImmediately();
					SphereDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);

					//Ѱ�ҵ�Ŀ�꣬Ȼ����Ŀ������(HomingPoint)������Ч��
					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHomingPoint());

					//����Timer��Ȼ�������г����˺�
					GetWorld()->GetTimerManager().SetTimer(ChainAttackTimer, this, &ARuleOfTheBullet::CurrentChianAttack, 0.4f,true);

					break;
				}
				}
			}
		}
	}


	//������󶨶�Ӧ�Ĺ��ܺ����ӿ�
	SphereDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);

}

// Called every frame
void ARuleOfTheBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheAIController* InstigatorAIController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter* TargetCharacter = Cast<ARuleOfTheCharacter>(InstigatorAIController->CurrentTarget.Get()))
			{
				switch (BulletType)
				{
					case EBulletType::BULLET_TRACK_LINE_SP:
					{
						if (TraceSpline)
						{
							//��ѡ��ȡʩ���ߺ�Ŀ��ľ���
							//��ȡTickTime
							//����Distance����Ҫ�������ű���  TickTime/���� )
							//��ȡ��Ӧ�����location��rotation ������
							FVector DistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
							CurrentTickTime += DeltaTime;

							//(CurrentTickTime / DistanceVector.Size()) ��������ٶ��Ǹ��ݳ��������б�������ʱ�䱣֤������
							float CurrentDistance = TraceSpline->GetSplineLength() * (CurrentTickTime / DistanceVector.Size() * 1000.f);

							FVector CurrentLoc = TraceSpline->GetWorldLocationAtDistanceAlongSpline(CurrentDistance);
							FRotator CurrentRot = TraceSpline->GetRotationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::Local);

							SetActorLocationAndRotation(CurrentLoc, CurrentRot);

							//��һ����Χ���ֶ�����beginOverlap
							if ((CurrentLoc-TargetCharacter->GetActorLocation()).Size()<=100.f)
							{
								//����HitResilt
								FHitResult HitResults;
								HitResults.Location = GetActorLocation();
								BeginOverlap(nullptr, TargetCharacter, nullptr, 0, false, HitResults);
							}

						}
						break;
					}
						case EBulletType::BULLET_CHAIN:
						{
						//ͨ��Tick��������Ŀ�귢������
						//���Ȼ���Ҫ��ȡ��Ŀ��
						//ͨ��Ŀ�����ϵ�����ϵͳ������һ������Ч����������

						//����һ�������������е������
						TArray<USceneComponent*> SceneComponents;
						RootComponent->GetChildrenComponents(true, SceneComponents);

						//ʹ���Զ���������ѭ��������
						for (auto& temp : SceneComponents)
						{
							if (UParticleSystemComponent* ParticleSystem = Cast<UParticleSystemComponent>(temp))
							{
								//��Ҫ����BeamSourcePoint��BeamTargetPoint
								ParticleSystem->SetBeamSourcePoint(0, InstigatorCharacter->GetOpenFirePoint()->GetComponentLocation(), 0);
								ParticleSystem->SetBeamTargetPoint(0, TargetCharacter->GetHomingPoint()->GetComponentLocation(), 0);
							}
						}
						break;
					}

				}
	
				if (!TargetCharacter->IsActive())
				{
					//���Ŀ��������Ҳ�����Լ�
					Destroy();
				}
			}
			else
			{
				//û��Ŀ�������
				Destroy();
			}

		}
	}
}

void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//		�ӵ��˺��ж��߼�
	// 		��1�� �����жϻ�ȡ��ʩ���ߣ��Լ��� Instigator��ʩ����(��̨����Monster)��
	// 		��2�� Ȼ���ȡ��OtherActor�Ƿ���Ч�����ˣ�
	// 		��3�� ֮���ж������ǲ���һ�������
	// 		��4�� �������һ���������ôҪ�̵㵱ǰOtherActor�����ˣ��Ƿ��ǻ��ŵ�
	// 		��5�� ������˻��ߣ���ô��������ЧȻ��ʹ��apply damage������˺���

		//���Instigator�Ƿ���Public�е�
	if (ARuleOfTheCharacter* InstigatorCharecter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheCharacter* OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor))
		{
			if (InstigatorCharecter != OtherCharacter)
			{
				if (InstigatorCharecter->IsTeam() != OtherCharacter->IsTeam())
				{
					if (OtherCharacter->IsActive())
					{
						//������Ч
						UGameplayStatics::SpawnEmitterAtLocation(this, DamageParticle, SweepResult.Location);

						//����˺�
						UGameplayStatics::ApplyDamage(OtherActor, 100.f, InstigatorCharecter->GetController(), InstigatorCharecter, UDamageType::StaticClass());

					}

					//���������������ӵ�����ײ���Զ�����
					switch (BulletType)
					{
					case EBulletType::BULLET_DIRECT_LINE:
					case EBulletType::BULLET_LINE:
					case EBulletType::BULLET_TRACK_LINE:
					case EBulletType::BULLET_TRACK_LINE_SP:
						Destroy();
						break;

					case EBulletType::BULLET_RANGE_LINE:
						RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));
						Destroy();
						break;
					}

				}
			}
		}
	}
}

void ARuleOfTheBullet::RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter)
{

	//���Ȼ��ʩ����
	//ֹͣProjectile�ƶ�
	//ʹ�õ�������ȡ�������е�ARuleOfCharacter
	//����ɸѡ���жϵ�ǰĿ�ꡣ
	//������룬�������С��1400�ͷ���
	//�ж�Ŀ����Ӫ��������ѷ��Ͳ�����˺�
	//���Ǿʹ�����ըЧ���Լ�����˺���

	if (InstigatorCharacter)
	{
		ProjectileComponent->StopMovementImmediately();
		TArray<AActor* >IgnoreActors;  //������������Actor�����ﷶΧ������Ҫ��ʹ�õľ�AActor�����顣

		for (TActorIterator<ARuleOfTheCharacter> it(GetWorld(), ARuleOfTheCharacter::StaticClass()); it; ++it)
		{
			if (ARuleOfTheCharacter* TargetCharacter = *it)
			{

				//�����Լ���Ŀ�����
				FVector TargetDistance = TargetCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
				if (TargetDistance.Size() <= 1400)
				{
					if (TargetCharacter->IsTeam() == InstigatorCharacter->IsTeam())
					{
						IgnoreActors.Add(TargetCharacter);
					}
					else
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, Origin);
					}
				}

			}
		}
		//��ɷ�Χ�˺���˥���棩
		UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), 100.f, 10.f, Origin, 400.f, 1000.f, 1.f, UDamageType::StaticClass(), IgnoreActors);
	}

}

void ARuleOfTheBullet::CurrentChianAttack()
{

	if (ChainAttackCount<0)
	{
		GetWorld()->GetTimerManager().ClearTimer(ChainAttackTimer);
		UKismetSystemLibrary::PrintString(this, (UKismetStringLibrary::Conv_IntToString(ChainAttackCount) + TEXT("Count Over")));
		return;
	}

	//���������ݼ�
	ChainAttackCount--;
	UKismetSystemLibrary::PrintString(this, UKismetStringLibrary::Conv_IntToString(ChainAttackCount));

	//�˺����㲿��
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheAIController* InstigatorControlelr = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter* TargetCharacter = Cast<ARuleOfTheCharacter>(InstigatorControlelr->CurrentTarget.Get()))
			{
				//��Ŀ������˺�
				UGameplayStatics::ApplyDamage(TargetCharacter, 100.f, InstigatorCharacter->GetController(), InstigatorCharacter, UDamageType::StaticClass());
			}
		}
	}
}


