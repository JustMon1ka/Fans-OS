// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "Backpack.generated.h"

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_FANS_OS_API UBackpack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackpack();

	// 背包容量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Backpack")
	int32 Capacity = 32;

	// 记录物品的TArray，键为物品的GUID，值为物品数量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Backpack")
	TArray<AItem*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	int32 FindItem(const AItem* Item) const noexcept;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// 尝试将一件物品添加进背包，成功返回true，失败返回false
	UFUNCTION(BlueprintCallable, Category = "Backpack Action")
	bool AddItemToBackpack(AItem* Item);

	// 将一件物品从背包删除
	UFUNCTION(BlueprintCallable, Category = "Backpack Action")
	void DeleteItemFromBackpack(const AItem* Item);

	// 将一件物品从背包删除一定数量
	UFUNCTION(BlueprintCallable, Category = "Backpack Action")
	void ReduceItemFromBackpack(const AItem* Item);
	

	// 背包UI的类
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BackpackUIClass;

	// 指向现在正在打开的背包UI类，如果为空则说明现在没有打开背包UI
	UPROPERTY()
	UUserWidget* BackpackUIInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBackpackOpening = false;
	
};
