// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h" // 需要引用 PlayerController 类
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBackpack::UBackpack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBackpack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

int32 UBackpack::FindItem(const AItem* Item) const noexcept
{
	if (Item == nullptr)
	{
		return -1;
	}
	int32 index = 0;
	while (index < Items.Num())
	{
		if (Item->GetGuid() == Items[index]->GetGuid())
		{
			return index;
		}
	}
	return -1;
}


// Called every frame
void UBackpack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBackpack::OpenBackpackUI()
{
	// 如果 UI 类已经设置且实例不存在，则加载并显示 UI
	if (BackpackUIClass && !BackpackUIInstance)
	{
		// 获取玩家控制器（或是游戏中的其他 UI 管理对象）
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			// 创建 UI 实例并将其添加到视口
			BackpackUIInstance = CreateWidget<UUserWidget>(PlayerController, BackpackUIClass);
			if (BackpackUIInstance)
			{
				BackpackUIInstance->AddToViewport();
			}
		}
	}
}

void UBackpack::CloseBackpackUI()
{
	if (BackpackUIInstance)
	{
		// 从视口中移除UI
		BackpackUIInstance->RemoveFromParent();

		// 清除UI实例引用
		BackpackUIInstance = nullptr;
	}
}

bool UBackpack::AddItemToBackpack(AItem* Item)
{
	if (Item == nullptr)
	{
		return false;
	}
	const int32 index = FindItem(Item);
	if (Capacity <= Items.Num() && (index < 0 || Item->IsMutex()))
	{
		return false; // 背包已满，无法加入新物品，只能合并已有可堆叠物品
	}
	if (index < 0)
	{
		Items.Add(Item); // 背包里没有，直接加入
		return true;
	}
	AItem* const item = Items[index];
	if (item->IsMutex())
	{
		Items.Add(Item); // 该物品不允许堆叠，直接加入
		return true;
	}
	item->SetNum(item->GetNum() + Item->GetNum());
	return true;
}

void UBackpack::DeleteItemFromBackpack(const AItem* const Item)
{
	if (Item == nullptr)
	{
		return;
	}
	const int32 index = FindItem(Item);
	if (index < 0)
	{
		return; // 未找到，直接返回
	}
	Items.RemoveAt(index); // 找到则删除
}

void UBackpack::ReduceItemFromBackpack(const AItem* const Item)
{
	if (Item == nullptr)
	{
		return;
	}
	const int32 index = FindItem(Item);
	if (index < 0)
	{
		return; // 未找到，直接返回
	}
	AItem* const item = Items[index];
	if (Item->GetNum() >= item->GetNum())
	{
		Items.RemoveAt(index);
		return;
	}
	item->SetNum(item->GetNum() - Item->GetNum());
}

