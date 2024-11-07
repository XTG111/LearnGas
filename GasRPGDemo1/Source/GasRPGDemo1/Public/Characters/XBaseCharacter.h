// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/XCombatInterface.h"
#include "XBaseCharacter.generated.h"


class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GASRPGDEMO1_API AXBaseCharacter : public ACharacter,public IAbilitySystemInterface,public IXCombatInterface
{
	GENERATED_BODY()

public:
	AXBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;
	virtual void InitialAbilityActorInfo();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	//Gas -- Only Use For Enemy
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//the initial attribute effect class
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DefaultAttributes | Primary")
	TSubclassOf<UGameplayEffect> InitialPrimaryEffectClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DefaultAttributes | Vital")
	TSubclassOf<UGameplayEffect> InitialVitalEffectClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DefaultAttributes | Secondary")
	TSubclassOf<UGameplayEffect> InitialSecondaryEffectClass;

	//use for use effect to initialize self attributes
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> effectclass, float level) const;
	void InitiaDefaultAttributes() const;
	
public:
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; };

};
