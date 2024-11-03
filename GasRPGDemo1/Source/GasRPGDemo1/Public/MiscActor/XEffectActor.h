// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h" //for FActiveGameplayEffectHandle
#include "GameFramework/Actor.h"
#include "XEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;


// use for control when apply and disapply
UENUM(BlueprintType)
enum class EEffectApplicationPolicy //add policy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy // remove policy just use for Infinite effect
{
	RemoveOnEndOverlap,
	DoNotRemove
};
//end

UCLASS()
class GASRPGDEMO1_API AXEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AXEffectActor();

protected:
	virtual void BeginPlay() override;

	//用于计算将Effect的效果作用于Actor
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* targetactor, TSubclassOf<UGameplayEffect> gameplayeffectclass);

	//用于控制是否销毁Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	//处理effectActor 与 targetActor接触的情况
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* targetactor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* targetactor);
	

	//GameplayEffectClass begin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InstanceEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	//GameplayEffectClass End

	//用于存储Infinite effect 和 ASC的关系，方便后续去除
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandlesMap;

	//Effect Level
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	float ActorLevel = 1.0f;
};
