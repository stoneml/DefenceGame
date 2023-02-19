// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <../DefenceGameType.h>
#include "GameFramework/Character.h"
#include "Interface/Character/RuleCharacter.h"
#include <Core/GameCore/TowerDefenceGamePlayerController.h>
#include <GameFramework/Actor.h>
#include <Core/GameCore/TowerDefenceGameState.h>
#include "UObject/NoExportTypes.h"
#include "RuleOfTheCharacter.generated.h"


UCLASS()
class DEFENCEGAME_API ARuleOfTheCharacter : public ACharacter, public IRuleCharacter
{
	GENERATED_BODY()

private:

	//最后那个meta参数是，允许Private访问(meta参数感觉无效，所以将他们设置为protected）

	//射线追踪对象
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* TraceShowCharacterInfomation;

	//开火点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* OpenFirePoint;

	//显示角色信息用的widget组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* Widget;

	//子弹追踪点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* HomingPoint;


public:
	// Sets default values for this character's properties
	ARuleOfTheCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	//获取当前Character模型用于进行摆放演示
	UFUNCTION(BlueprintCallable, Category = "Tower|Test")
	UStaticMesh* GetDollMesh();

	//更新血量
	void UpdateUI();

	//创建一个Drawtext
	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<class ADrawText> DrawTextClass;


public:

	//继承接口的返回角色类型
	virtual EGameCharacterType::Type GetType();

	virtual bool IsDeath()override;
	virtual	float GetHealth()override;
	virtual float GetMaxHealth()override;
	virtual bool IsTeam()override;

	//从接口中调用获取数据的接口
	virtual FCharacterData& GetCharacterData() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//UE自己的受伤函数
	//伤害的数值
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	//获取GameController
	//使用转换的方法
	//FORCEINLINE ATowerDefenceGamePlayerController* GetGamePlayerController() { return GetWorld() ? (Cast<ATowerDefenceGamePlayerController>(GetWorld()->GetFirstPlayerController())): nullptr; }
	//通过模板方式获取
	FORCEINLINE ATowerDefenceGamePlayerController* GetGamePlayerController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowerDefenceGamePlayerController>() : nullptr; }

	//获取GameState
	FORCEINLINE ATowerDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowerDefenceGameState>() : nullptr; }


public:
	//加上Const是为了保证函数内部的东西不被修改

	//暴露跟踪点
	FORCEINLINE USceneComponent* GetHomingPoint() const { return HomingPoint; }
	//暴露开火点
	FORCEINLINE UArrowComponent* GetOpenFirePoint() const { return OpenFirePoint; }

	//将塔的当前情况返给蓝图，让蓝图判断塔是否存活
	//这里返回的要是反向的
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Towers|Attribute")
	bool IsActive() { return !IsDeath(); }



public:

	//暴露给AnimInstance蓝图，通知是否进行攻击
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttibute")
		bool bAttack;

	//角色ID
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttibute")
	FGuid CurrentGUID;

	FCharacterData TargetCharacterData;

	//输入功能在Controller中实现，所以不需要在Pawn中还有
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
