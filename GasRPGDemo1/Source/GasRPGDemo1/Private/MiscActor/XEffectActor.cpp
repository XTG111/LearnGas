// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscActor/XEffectActor.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystems/XAttributeSet.h>
#include "AbilitySystemBlueprintLibrary.h"

AXEffectActor::AXEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AXEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AXEffectActor::ApplyEffectToTarget(AActor* targetactor, TSubclassOf<UGameplayEffect> gameplayeffectclass)
{
	//获取AbilitySystemComponent
	//1. 可以通过继承了IAbilitySystemInterface的Actor
	//2. 利用UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent，
	//该函数可以在没有继承IAbilitySystemInterface的时候，检测actor是否有UAbilitySystemComponent
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetactor);
	if (TargetASC == nullptr) return;

	check(gameplayeffectclass);
	//为了给target添加effect，利用ApplyGameplayEffectSpecToSelf()
	//需要参数FGameplayEffectSpec，通过FGameplayEffectSpecHandle获得 -- MakeOutgoingSpec

	//MakeOutgoingSpec需要参数 FGameplayEffectContextHandle
	//FGameplayEffectContext就是存储的该effect的一些信息
	
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); // 添加导致该Effect的Actor信息
		
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(gameplayeffectclass,ActorLevel,EffectContextHandle);	
	
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//获取当前effect的DurationPolicy, 只有在Infinite下才会考虑手动去除
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandlesMap.Add(ActiveGameplayEffectHandle,TargetASC);
	}
	
}

void AXEffectActor::OnOverlap(AActor* targetactor)
{
	if(InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(targetactor, InstanceGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(targetactor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(targetactor, InfiniteGameplayEffectClass);
	}
}

void AXEffectActor::OnEndOverlap(AActor* targetactor)
{
	if(InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(targetactor, InstanceGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(targetactor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy ==  EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(targetactor, InfiniteGameplayEffectClass);
	}
	//去除
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetactor);
		if (TargetASC == nullptr) return;

		TArray<FActiveGameplayEffectHandle> ActiveHandleToRemoveArray; //存储需要溢出的effect
		//遍历ActiveEffectHandlesMap 如果当前的ASC == TargetASC, 那么去除
		for(auto& HandlePair : ActiveEffectHandlesMap)
		{
			if(HandlePair.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				ActiveHandleToRemoveArray.Add(HandlePair.Key);				
			}
		}
		//从ActiveEffectHandlesMap移除ActiveHandleToRemoveArray
		for(auto& RemoveHandle : ActiveHandleToRemoveArray)
		{
			ActiveEffectHandlesMap.FindAndRemoveChecked(RemoveHandle);
		}
	}
}

