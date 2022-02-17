// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/AnimNotify/AnimNotify_SpawnBullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Character/Bullet/RuleOfTheBullet.h"
#include "Components/ArrowComponent.h"
#include "Math/TransformVectorized.h"

UAnimNotify_SpawnBullet::UAnimNotify_SpawnBullet()
	:Super()
{

#if WITH_EDITORONLY_DATA
	InSocketName = TEXT("OpenFire");  //初始化一个名字，这个名字是骨骼的名字
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA

}

FString UAnimNotify_SpawnBullet::GetNotifyName_Implementation() const
{
	//判断BulletClass的有效性然后返回名字
	if (BulletClass)
	{
		return BulletClass->GetName();
	}
	else
	{
		//使用父类函数
		return Super::GetNotifyName_Implementation();
	}
}



void UAnimNotify_SpawnBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 子弹生成
	//	a. 生成子弹需要Tower获得World，然后通过SkeletalMeshComponent来获取当前使用节点的上一层（现在也就是tower），使用MeshComp的getowner。
	// （注意需要添加SkeletalMesh的头文件）
	//	b. 通过获取到的Charater然后进行getWorld并且进行spawn Actor
	//	c. 添加Transform的时候，可以直接使用FRotator和FVector（位置在需要使用Character的OpenFirePoint的位置）
	//	d. 获取子弹发射的位置，也就是OpenFire的位置。

#if WITH_EDITOR

	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
#else

	//这套方法只是和在runtime情况下，看到子弹发射。
	if (ARuleOfTheCharacter* Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter())) //这里获取到骨骼使用的是GetOuter
	{
		FVector ComponentLocation = Character->GetOpenFirePoint()->GetComponentLocation();
		FRotator ComponentRotation = Character->GetOpenFirePoint()->GetComponentRotation();
	}

#endif
	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))  //这里获取到骨骼使用的是GetOuter
	{
		//设置炮台Transform和SpawnParamter参数。
		FTransform BulletTransform;
		BulletTransform.SetLocation(ComponentLocation);
		BulletTransform.SetRotation(ComponentRotation.Quaternion());

		FActorSpawnParameters ActorSpawnParameter;
		ActorSpawnParameter.Instigator = Cast<APawn>(Character);

/*  暂时放弃使用
#if !WITH_EDITOR
		//在非编辑模式下才进行赋值，也就是运行时赋值
		ActorSpawnParameter.Instigator = Character;  //这个施法者就是炮台/敌人自己。
#endif*/

		//找到后向下执行
		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, BulletTransform, ActorSpawnParameter))
		{

		}

	}






/*
	//旧版本代码
	if (ARuleOfTheCharacter* Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter()))
	{
		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, Character->GetOpenFirePoint()->GetComponentLocation()
			, Character->GetOpenFirePoint()->GetComponentRotation()))
		{

		}
	}*/

}
