// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "SkillData.h"
#include "CharacterData.generated.h"

/**
 * 
 */

/*
Struct定义和使用
类是引用类型，是保存在托管堆中的。通过定义类，我们可以在数据的生存期上得到很高的灵活性，但是也会让程序的性能有一定的损失。
虽然这种损失很小，但当我们只需要定义一个很小的结构时，用类来定义就有些浪费，对于这样的问题，C#有相对应的方案来解决，那就是－结构(struct)。

结构(struct)是一种值类型。也就是说，结构实例是分配在线程堆栈上的，结构本身是包含有值的，而不是像类一样的引用类型，包含的是所指向堆当中的引用（指针）。
也就是说，结构的生存周期与简单类型（int, double等）相同的。所以说我们在定义较小的类时，可以尽量使用结构。

结构与类的区别：

（1）结构是值类型，不是引用类型。

（2）结构可以继承接口，但是不可以继承类或结构。

（3）结构的构造方法的工作方式有所不同，只能声明带参数的构造方法，且不能声明析构方法。

（4）可以指定字段如何在内存中布局。

什么时候使用（struct）结构：

虽然我们可以用(class)类完全代替(struct)结构，但是为了程序的性能的提高，建议大家在实现一个用于存储数据或数据量较小的结构时来使用结构，
因为结构是值类型，所以在性能的影响上，是能起到正面作用的。
*/


//这里继承FTableRowBase是为了能够在蓝图中以这个类创建DataTable
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{

	GENERATED_BODY()

public:

	FCharacterData();

	//玩家名字
	UPROPERTY(EditDefaultsOnly,Category = "Character Attribute")
	FName Name;

/*
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Character Attribute")
	FString GUID;*/

	//玩家ID
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	int32 CharacterID;


	//玩家等级
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Character Attribute")
	int32 CurLevel;

	//最大血量
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxHealth;

	//血量
	UPROPERTY()
	float Health;

	//基础攻击力
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float PhysicalAttack;

	//攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float AttackSpeed;

	//护甲
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Armor;

	//最大经验值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxEmpircalValue;

	//经验值
	UPROPERTY()
	float EmpiraclValue;

	//技能冷却时间
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float CoolDown;

	//金币
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Gold;

	//角色介绍
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	FText Introduction;


	//角色增益属性
	/************************************************************/

	//添加金币
	UPROPERTY(EditDefaultsOnly,Category ="Character Profit")
	float AddGold;

	//添加生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddHealth;

	//增加攻击力
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddPhysicalAttack;

	//增加护甲
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddArmor;

	//增加升级需要的经验值
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddEmpircalValue;

	//增加攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddAttackSpeed;

	//增加自动恢复血量
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float RestoreHealth;


	//塔技能
	/************************************************************/
	
	//添加被动生命值
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillHealth;

	//添加持续恢复生命值
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddContinueHealth;

	//添加被动攻击力
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillPhysicalAttack;

	//增加防御力
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillArmor;

	//增加攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillAtteckSpeed;

	//减少技能CD
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float ReducePassiveSkillCDTime;

	//塔的建造时间
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	float ConstructionTime;


	//技能列表
	/************************************************************/

	//塔技能
	//@Param 等级，技能内容
	UPROPERTY(EditDefaultsOnly,Category = "Skill")
	TMap<int32,FSkillData>CharacterSkills;



public:

	//资源  两种方法都能获取对应数据
	//////////////////////////////////////////////////////////////
	//角色蓝图实例
	UPROPERTY(EditDefaultsOnly,Category = "Table")
	TAssetSubclassOf<class ARuleOfTheCharacter> CharacterBlueprintKey;

	//角色图标
	UPROPERTY(EditDefaultsOnly,Category = "Table")
	TAssetPtr<class UTexture2D> ICon;


public:

	//返回函数,判断是否有效
	bool IsValid() const;

	//更新血量
	void UpdateHealth();

};








/*
  //旧版本
UCLASS()
class DEFENCEGAME_API UCharacterData : public UObject
{
	GENERATED_BODY()





};
*/
