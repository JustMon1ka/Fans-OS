// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItem.h"  // 引入DropItem类
#include "WeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy.generated.h"

class AWeaponActor;

UCLASS()
class FPS_FANS_OS_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;



	/** 自定义伤害处理函数 */
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(float DamageAmount);

	// 生命值，编辑时可修改
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float CurrentHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MaxHealth = 100;

	// 敌人的名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FName Name = "enemy";

	// 骨骼网格体组件，编辑时可指定骨骼网格体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	USkeletalMeshComponent* SkeletalMeshComponent;

	// 枚举掉落物的静态网格体类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AActor>> DropItemBlueprintClasses;

	// 敌人死亡时玩家获得的经验
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Exp = 10;

	// 敌人死亡时调用的方法
	UFUNCTION(BlueprintCallable, Category = "Enemy")


	void Dead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 掉落物生成的函数
	void SpawnDropItems();

	// 触发死亡动画或其他逻辑
	void TriggerDeathAnimation();

	// 更新角色的杀敌任务
	void UpdateKillingEnemyTask();

	// 给予玩家经验
	void UpdatePlayerExp();

private:
	bool IsDead();
};
