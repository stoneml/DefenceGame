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
Struct�����ʹ��
�����������ͣ��Ǳ������йܶ��еġ�ͨ�������࣬���ǿ��������ݵ��������ϵõ��ܸߵ�����ԣ�����Ҳ���ó����������һ������ʧ��
��Ȼ������ʧ��С����������ֻ��Ҫ����һ����С�Ľṹʱ���������������Щ�˷ѣ��������������⣬C#�����Ӧ�ķ�����������Ǿ��ǣ��ṹ(struct)��

�ṹ(struct)��һ��ֵ���͡�Ҳ����˵���ṹʵ���Ƿ������̶߳�ջ�ϵģ��ṹ�����ǰ�����ֵ�ģ�����������һ�����������ͣ�����������ָ��ѵ��е����ã�ָ�룩��
Ҳ����˵���ṹ����������������ͣ�int, double�ȣ���ͬ�ġ�����˵�����ڶ����С����ʱ�����Ծ���ʹ�ýṹ��

�ṹ���������

��1���ṹ��ֵ���ͣ������������͡�

��2���ṹ���Լ̳нӿڣ����ǲ����Լ̳����ṹ��

��3���ṹ�Ĺ��췽���Ĺ�����ʽ������ͬ��ֻ�������������Ĺ��췽�����Ҳ�����������������

��4������ָ���ֶ�������ڴ��в��֡�

ʲôʱ��ʹ�ã�struct���ṹ��

��Ȼ���ǿ�����(class)����ȫ����(struct)�ṹ������Ϊ�˳�������ܵ���ߣ���������ʵ��һ�����ڴ洢���ݻ���������С�Ľṹʱ��ʹ�ýṹ��
��Ϊ�ṹ��ֵ���ͣ����������ܵ�Ӱ���ϣ��������������õġ�
*/


//����̳�FTableRowBase��Ϊ���ܹ�����ͼ��������ഴ��DataTable
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{

	GENERATED_BODY()

public:

	FCharacterData();

	//�������
	UPROPERTY(EditDefaultsOnly,Category = "Character Attribute")
	FName Name;

/*
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Character Attribute")
	FString GUID;*/

	//���ID
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	int32 CharacterID;


	//��ҵȼ�
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Character Attribute")
	int32 CurLevel;

	//���Ѫ��
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxHealth;

	//Ѫ��
	UPROPERTY()
	float Health;

	//����������
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float PhysicalAttack;

	//�����ٶ�
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float AttackSpeed;

	//����
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Armor;

	//�����ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxEmpircalValue;

	//����ֵ
	UPROPERTY()
	float EmpiraclValue;

	//������ȴʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float CoolDown;

	//���
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Gold;

	//��ɫ����
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	FText Introduction;


	//��ɫ��������
	/************************************************************/

	//��ӽ��
	UPROPERTY(EditDefaultsOnly,Category ="Character Profit")
	float AddGold;

	//�������ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddHealth;

	//���ӹ�����
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddPhysicalAttack;

	//���ӻ���
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddArmor;

	//����������Ҫ�ľ���ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddEmpircalValue;

	//���ӹ����ٶ�
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddAttackSpeed;

	//�����Զ��ָ�Ѫ��
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float RestoreHealth;


	//������
	/************************************************************/
	
	//��ӱ�������ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillHealth;

	//��ӳ����ָ�����ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddContinueHealth;

	//��ӱ���������
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillPhysicalAttack;

	//���ӷ�����
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillArmor;

	//���ӹ����ٶ�
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillAtteckSpeed;

	//���ټ���CD
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float ReducePassiveSkillCDTime;

	//���Ľ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	float ConstructionTime;


	//�����б�
	/************************************************************/

	//������
	//@Param �ȼ�����������
	UPROPERTY(EditDefaultsOnly,Category = "Skill")
	TMap<int32,FSkillData>CharacterSkills;



public:

	//��Դ  ���ַ������ܻ�ȡ��Ӧ����
	//////////////////////////////////////////////////////////////
	//��ɫ��ͼʵ��
	UPROPERTY(EditDefaultsOnly,Category = "Table")
	TAssetSubclassOf<class ARuleOfTheCharacter> CharacterBlueprintKey;

	//��ɫͼ��
	UPROPERTY(EditDefaultsOnly,Category = "Table")
	TAssetPtr<class UTexture2D> ICon;


public:

	//���غ���,�ж��Ƿ���Ч
	bool IsValid() const;

	//����Ѫ��
	void UpdateHealth();

};








/*
  //�ɰ汾
UCLASS()
class DEFENCEGAME_API UCharacterData : public UObject
{
	GENERATED_BODY()





};
*/
