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
	InSocketName = TEXT("OpenFire");  //��ʼ��һ�����֣���������ǹ���������
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA

}

FString UAnimNotify_SpawnBullet::GetNotifyName_Implementation() const
{
	//�ж�BulletClass����Ч��Ȼ�󷵻�����
	if (BulletClass)
	{
		return BulletClass->GetName();
	}
	else
	{
		//ʹ�ø��ຯ��
		return Super::GetNotifyName_Implementation();
	}
}



void UAnimNotify_SpawnBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// �ӵ�����
	//	a. �����ӵ���ҪTower���World��Ȼ��ͨ��SkeletalMeshComponent����ȡ��ǰʹ�ýڵ����һ�㣨����Ҳ����tower����ʹ��MeshComp��getowner��
	// ��ע����Ҫ���SkeletalMesh��ͷ�ļ���
	//	b. ͨ����ȡ����CharaterȻ�����getWorld���ҽ���spawn Actor
	//	c. ���Transform��ʱ�򣬿���ֱ��ʹ��FRotator��FVector��λ������Ҫʹ��Character��OpenFirePoint��λ�ã�
	//	d. ��ȡ�ӵ������λ�ã�Ҳ����OpenFire��λ�á�

#if WITH_EDITOR

	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
#else

	//���׷���ֻ�Ǻ���runtime����£������ӵ����䡣
	if (ARuleOfTheCharacter* Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter())) //�����ȡ������ʹ�õ���GetOuter
	{
		FVector ComponentLocation = Character->GetOpenFirePoint()->GetComponentLocation();
		FRotator ComponentRotation = Character->GetOpenFirePoint()->GetComponentRotation();
	}

#endif
	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))  //�����ȡ������ʹ�õ���GetOuter
	{
		//������̨Transform��SpawnParamter������
		FTransform BulletTransform;
		BulletTransform.SetLocation(ComponentLocation);
		BulletTransform.SetRotation(ComponentRotation.Quaternion());

		FActorSpawnParameters ActorSpawnParameter;
		ActorSpawnParameter.Instigator = Cast<APawn>(Character);

/*  ��ʱ����ʹ��
#if !WITH_EDITOR
		//�ڷǱ༭ģʽ�²Ž��и�ֵ��Ҳ��������ʱ��ֵ
		ActorSpawnParameter.Instigator = Character;  //���ʩ���߾�����̨/�����Լ���
#endif*/

		//�ҵ�������ִ��
		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, BulletTransform, ActorSpawnParameter))
		{

		}

	}






/*
	//�ɰ汾����
	if (ARuleOfTheCharacter* Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter()))
	{
		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, Character->GetOpenFirePoint()->GetComponentLocation()
			, Character->GetOpenFirePoint()->GetComponentRotation()))
		{

		}
	}*/

}
