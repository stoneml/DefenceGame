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

	//����Ǹ�meta�����ǣ�����Private����(meta�����о���Ч�����Խ���������Ϊprotected��

	//����׷�ٶ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* TraceShowCharacterInfomation;

	//�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* OpenFirePoint;

	//��ʾ��ɫ��Ϣ�õ�widget���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* Widget;

	//�ӵ�׷�ٵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* HomingPoint;


public:
	// Sets default values for this character's properties
	ARuleOfTheCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	//��ȡ��ǰCharacterģ�����ڽ��аڷ���ʾ
	UFUNCTION(BlueprintCallable, Category = "Tower|Test")
	UStaticMesh* GetDollMesh();

	//����Ѫ��
	void UpdateUI();

	//����һ��Drawtext
	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<class ADrawText> DrawTextClass;


public:

	//�̳нӿڵķ��ؽ�ɫ����
	virtual EGameCharacterType::Type GetType();

	virtual bool IsDeath()override;
	virtual	float GetHealth()override;
	virtual float GetMaxHealth()override;
	virtual bool IsTeam()override;

	//�ӽӿ��е��û�ȡ���ݵĽӿ�
	virtual FCharacterData& GetCharacterData() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//UE�Լ������˺���
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;




	//��ȡGameController
	//ʹ��ת���ķ���
	//FORCEINLINE ATowerDefenceGamePlayerController* GetGamePlayerController() { return GetWorld() ? (Cast<ATowerDefenceGamePlayerController>(GetWorld()->GetFirstPlayerController())): nullptr; }
	FORCEINLINE ATowerDefenceGamePlayerController* GetGamePlayerController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowerDefenceGamePlayerController>() : nullptr; }

	//��ȡGameState
	FORCEINLINE ATowerDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowerDefenceGameState>() : nullptr; }





public:
	//����Const��Ϊ�˱�֤�����ڲ��Ķ��������޸�

	//��¶���ٵ�
	FORCEINLINE USceneComponent* GetHomingPoint() const { return HomingPoint; }
	//��¶�����
	FORCEINLINE UArrowComponent* GetOpenFirePoint() const { return OpenFirePoint; }

	//�����ĵ�ǰ���������ͼ������ͼ�ж����Ƿ���
	//���ﷵ�ص�Ҫ�Ƿ����
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Towers|Attribute")
	bool IsActive() { return !IsDeath(); }



public:

	//��¶��AnimInstance��ͼ��֪ͨ�Ƿ���й���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttibute")
		bool bAttack;

	//��ɫID
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttibute")
	FGuid CurrentGUID;


	FCharacterData TargetCharacterData;



	//���빦����Controller��ʵ�֣����Բ���Ҫ��Pawn�л���
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
