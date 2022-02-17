// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ARuleOfTheCharacter;
class IRuleCharacter;
class UStaticMesh;
class UWorld;



//因为这个DefenceGameUtils类使用的是Namespace，所以直接就可以用::来获取

namespace DefenceGameUtils
{

	//找寻最近的目标
	// @Parm 放入指定的Actor数组来进行盘点
	// @Parm 放入需要被比对的Pawn的位置
	ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& InLocation);

}


namespace Expression
{
	//伤害计算的公式
	//@Parm1 攻击的目标
	//@Parm2 受伤的角色
	float CalcDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner);

}


namespace MeshUtils
{
	//蒙皮网格转换为StatciMesh
	//@ 传入一个World，为了让Mesh和这个World捆绑在一起
	//@ 传入一个SkeletalMeshComponent
	// 返回一个StaticMesh

	UStaticMesh* SkeletalCompToStaticMesh(UWorld* World,USkeletalMeshComponent* SkeletalMeshComp);




}