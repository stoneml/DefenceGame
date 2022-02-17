// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ARuleOfTheCharacter;
class IRuleCharacter;
class UStaticMesh;
class UWorld;



//��Ϊ���DefenceGameUtils��ʹ�õ���Namespace������ֱ�ӾͿ�����::����ȡ

namespace DefenceGameUtils
{

	//��Ѱ�����Ŀ��
	// @Parm ����ָ����Actor�����������̵�
	// @Parm ������Ҫ���ȶԵ�Pawn��λ��
	ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& InLocation);

}


namespace Expression
{
	//�˺�����Ĺ�ʽ
	//@Parm1 ������Ŀ��
	//@Parm2 ���˵Ľ�ɫ
	float CalcDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner);

}


namespace MeshUtils
{
	//��Ƥ����ת��ΪStatciMesh
	//@ ����һ��World��Ϊ����Mesh�����World������һ��
	//@ ����һ��SkeletalMeshComponent
	// ����һ��StaticMesh

	UStaticMesh* SkeletalCompToStaticMesh(UWorld* World,USkeletalMeshComponent* SkeletalMeshComp);




}