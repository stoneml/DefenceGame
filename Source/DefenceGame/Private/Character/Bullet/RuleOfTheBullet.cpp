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

	//组件创建
	SphereDamage = CreateDefaultSubobject<USphereComponent>(TEXT("BulletDamage"));
	RootBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRootBullet"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectileComponent"));

	//组件绑定
	RootComponent = RootBullet;
	SphereDamage->AttachToComponent(RootBullet, FAttachmentTransformRules::KeepRelativeTransform);

	//设置弹射组件的初始状态
	ProjectileComponent->MaxSpeed = 2000.f;
	ProjectileComponent->InitialSpeed = 1600.f;
	ProjectileComponent->ProjectileGravityScale = 0.f;  //设置重力为0
	ProjectileComponent->UpdatedComponent = SphereDamage;  //效果影响到对应的组件

	BulletType = EBulletType::BULLET_DIRECT_LINE;

	//设置子弹存活时间
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

				//通过类型初始化子弹状态
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

					//首先获取施法者（发射子弹的Actor）
					//通过当前对象的controller获取基类Controller，然后获取到目标
					//获取到controller中的target（这个target是弱指针，需要使用.Get() 来进行转换为裸指针）
					//设置子弹的弹射设置，HomingAccelerationMagnitude（当前追踪目标的加速度大小），设置为4000
					//添加HomingTargetComponent为目标身上的HomingTarget

					ProjectileComponent->HomingAccelerationMagnitude = 4000.f;
					ProjectileComponent->HomingTargetComponent = TargetCharacter->GetHomingPoint();

				}
				break;
				case EBulletType::BULLET_TRACK_LINE_SP:
				{
					//首先需要在发射时生成特效。
					ProjectileComponent->StopMovementImmediately();
					UGameplayStatics::SpawnEmitterAtLocation(this, OpenFireParticle, GetActorLocation());
					TraceSpline = NewObject<USplineComponent>(this, TEXT("TraceSpline"));
					TraceSpline->RegisterComponent();

					//● 创建Spline，然后第一个点的位置是炮弹自身位置
					//● 减法，减谁就加上谁，得到的就是终点的位置。（前提A大于B）
					//● 然后设置高度
					//● //这里的Y轴便宜是可以自定义的，让子弹飞起来更扭曲。
					//● 刚才计算的位置最后设置给点一。
					//● 最后就是添加一个点位，最后这个点位就是放在敌人的位置(位置空间为Local)。
					//● 因为是按照Spline来进行移动，所以这里直接就停止了ProjectileMovement的移动操作。

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

					//首先获取施法者
					//获取施法者的Controller 为了获取其中的Target (Target需要获取BaseController来获取）
					//获取Target并转换为ARuleOfCharacter
					//开启ProjectileMovement的重力。
					//计算炮弹和Target的距离。
					//通过 t = S/v 计算出时间 （三维的）
					//通过 gt计算得到Y轴的值。
					//通过初始速度 v * t 计算出X轴向的长度。
					//通过勾股定理计算出发射是的 v的速度。
					//通过公式进行发射弧度cos计算(反余弦）。(需要乘以 c = PI*0.1）
					//然后将弧度转为角度 = 弧度 * （180 / PI）
					//最后设置炮弹旋转值
					//给Porjectile重新设定一个速度，X 轴向正方向* 发射初始速度

					ProjectileComponent->ProjectileGravityScale = 1.f;  //设置重力
				/*	FVector DistanceVector = Target->GetActorLocation() - GetActorLocation();

					float InTime = DistanceVector.Size() / (ProjectileComponent->InitialSpeed);
					float Y = ProjectileComponent->GetGravityZ() * InTime;	//Y方向高度
					float X = ProjectileComponent->InitialSpeed * InTime;  //X方向长度

					float V = FMath::Sqrt(X * X + Y * Y);  //勾股定理计算
					float CosRadian = FMath::Acos(DistanceVector.Size() / (V * (InTime * (PI * 0.1f))));
					FRotator Rot = GetActorRotation();
					Rot.Pitch = CosRadian * (180 / PI);
					SetActorRotation(Rot);*/

					//这个伤害有问题。
					FVector DistanceVector = TargetCharacter->GetActorLocation() - GetActorLocation();
					float InTime = DistanceVector.Size() / ProjectileComponent->InitialSpeed;

					// tan 对边与邻边的比值
					float TanRadian = FMath::Atan(((ProjectileComponent->GetGravityZ() * (InTime)) * (PI * 0.1f)) / (DistanceVector.Size() / 2));
					FRotator Rot = GetActorRotation();
					//Rot.Pitch = TanRadian*(180/PI);
					Rot.Pitch = TanRadian;
					SetActorRotation(Rot);

					//重新设定速度
					ProjectileComponent->SetVelocityInLocalSpace(FVector(1.f, 0.f, 0.f) * ProjectileComponent->InitialSpeed);
				}
				break;
				case EBulletType::BULLET_RANGE:

					//首先获得施法者
					//停止Projectile移动
					//使用迭代器获取场景所有的ARuleOfCharacter
					//迭代筛选，判断当前目标是否可以转为ARuleOfCharacter
					//计算距离，如果距离小于1400就发射
					//判断目标阵营，如果是友方就不造成伤害
					//不是就触发爆炸效果以及造成伤害。

					SphereDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					//调用范围伤害函数。
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));

					/*
							if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
							{
								ProjectileComponent->StopMovementImmediately();
								TArray<AActor*>IgnoreActors; //忽略的目标
								//TArray<ARuleOfTheCharacter*>TargetCharacter;  //地推目标
								for (TActorIterator<ARuleOfTheCharacter> it(GetWorld(),ARuleOfTheCharacter::StaticClass());it; ++it)
								{
									if (ARuleOfTheCharacter* TheCharacter = *it)  //判断目标是否能转换成对应的Character
									{
										//想目标开火后，判断伤害范围内的其他目标与炮弹自身的距离
										FVector TargetDistance = TheCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
										if (TargetDistance.Size()<=1400.f)
										{
											if (TheCharacter->IsTeam() == InstigatorCharacter->IsTeam())
											{
												IgnoreActors.Add(TheCharacter);
											}
											else
											{
												//不是一个队的就攻击。
												UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, TheCharacter->GetActorLocation());
												//TargetCharacter.Add(TheCharacter);
											}
										}
									}
								}

								//范围攻击
								UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), 100.f, 10.f, GetActorLocation(), 400.f, 1000.f, 1.f, UDamageType::StaticClass(), IgnoreActors, InstigatorCharacter);

							}*/
				break;
				case EBulletType::BULLET_CHAIN:
				{

					ProjectileComponent->StopMovementImmediately();
					SphereDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);

					//寻找到目标，然后在目标身上(HomingPoint)生成特效。
					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHomingPoint());

					//设置Timer，然后来进行持续伤害
					GetWorld()->GetTimerManager().SetTimer(ChainAttackTimer, this, &ARuleOfTheBullet::CurrentChianAttack, 0.4f,true);

					break;
				}
				}
			}
		}
	}


	//启动后绑定对应的功能函数接口
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
							//首选获取施法者和目标的距离
							//获取TickTime
							//计算Distance（需要考虑缩放比例  TickTime/距离 )
							//获取对应距离的location和rotation 并设置
							FVector DistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
							CurrentTickTime += DeltaTime;

							//(CurrentTickTime / DistanceVector.Size()) 这个控制速度是根据长度来进行比例缩放时间保证是匀速
							float CurrentDistance = TraceSpline->GetSplineLength() * (CurrentTickTime / DistanceVector.Size() * 1000.f);

							FVector CurrentLoc = TraceSpline->GetWorldLocationAtDistanceAlongSpline(CurrentDistance);
							FRotator CurrentRot = TraceSpline->GetRotationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::Local);

							SetActorLocationAndRotation(CurrentLoc, CurrentRot);

							//在一定范围内手动调用beginOverlap
							if ((CurrentLoc-TargetCharacter->GetActorLocation()).Size()<=100.f)
							{
								//创建HitResilt
								FHitResult HitResults;
								HitResults.Location = GetActorLocation();
								BeginOverlap(nullptr, TargetCharacter, nullptr, 0, false, HitResults);
							}

						}
						break;
					}
						case EBulletType::BULLET_CHAIN:
						{
						//通过Tick来持续对目标发射射线
						//首先还是要获取到目标
						//通过目标身上的粒子系统来赋予一个闪电效果在他身上

						//创建一个数组来接所有的子组件
						TArray<USceneComponent*> SceneComponents;
						RootComponent->GetChildrenComponents(true, SceneComponents);

						//使用自动搜索类型循环来遍历
						for (auto& temp : SceneComponents)
						{
							if (UParticleSystemComponent* ParticleSystem = Cast<UParticleSystemComponent>(temp))
							{
								//需要设置BeamSourcePoint和BeamTargetPoint
								ParticleSystem->SetBeamSourcePoint(0, InstigatorCharacter->GetOpenFirePoint()->GetComponentLocation(), 0);
								ParticleSystem->SetBeamTargetPoint(0, TargetCharacter->GetHomingPoint()->GetComponentLocation(), 0);
							}
						}
						break;
					}

				}
	
				if (!TargetCharacter->IsActive())
				{
					//如果目标死亡了也销毁自己
					Destroy();
				}
			}
			else
			{
				//没有目标就销毁
				Destroy();
			}

		}
	}
}

void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//		子弹伤害判断逻辑
	// 		（1） 首先判断获取到施法者（自己） Instigator（施法者(炮台或者Monster)）
	// 		（2） 然后获取到OtherActor是否有效（敌人）
	// 		（3） 之后判断他们是不是一个队伍的
	// 		（4） 如果不是一个队伍的那么要盘点当前OtherActor（敌人）是否是活着的
	// 		（5） 如果敌人或者，那么就生成特效然后使用apply damage来造成伤害。

		//这个Instigator是放在Public中的
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
						//生成特效
						UGameplayStatics::SpawnEmitterAtLocation(this, DamageParticle, SweepResult.Location);

						//造成伤害
						UGameplayStatics::ApplyDamage(OtherActor, 100.f, InstigatorCharecter->GetController(), InstigatorCharecter, UDamageType::StaticClass());

					}

					//满足以上条件的子弹，碰撞后自动销毁
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

	//首先获得施法者
	//停止Projectile移动
	//使用迭代器获取场景所有的ARuleOfCharacter
	//迭代筛选，判断当前目标。
	//计算距离，如果距离小于1400就发射
	//判断目标阵营，如果是友方就不造成伤害
	//不是就触发爆炸效果以及造成伤害。

	if (InstigatorCharacter)
	{
		ProjectileComponent->StopMovementImmediately();
		TArray<AActor* >IgnoreActors;  //创建忽略数组Actor，这里范围攻击需要，使用的就AActor的数组。

		for (TActorIterator<ARuleOfTheCharacter> it(GetWorld(), ARuleOfTheCharacter::StaticClass()); it; ++it)
		{
			if (ARuleOfTheCharacter* TargetCharacter = *it)
			{

				//计算自己和目标距离
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
		//造成范围伤害（衰减版）
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

	//攻击次数递减
	ChainAttackCount--;
	UKismetSystemLibrary::PrintString(this, UKismetStringLibrary::Conv_IntToString(ChainAttackCount));

	//伤害计算部分
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheAIController* InstigatorControlelr = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter* TargetCharacter = Cast<ARuleOfTheCharacter>(InstigatorControlelr->CurrentTarget.Get()))
			{
				//对目标造成伤害
				UGameplayStatics::ApplyDamage(TargetCharacter, 100.f, InstigatorCharacter->GetController(), InstigatorCharacter, UDamageType::StaticClass());
			}
		}
	}
}


