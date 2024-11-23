// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystems/XAbilitySystemComponent.h"

AXBaseCharacter::AXBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("HandWeaponSocket"));

}

UAbilitySystemComponent* AXBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AXBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXBaseCharacter::InitialAbilityActorInfo()
{
}

void AXBaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> effectclass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(effectclass);	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(effectclass,level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AXBaseCharacter::InitiaDefaultAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(InitialPrimaryEffectClass);
	check(InitialSecondaryEffectClass);
	check(InitialVitalEffectClass);
	ApplyEffectToSelf(InitialPrimaryEffectClass,1.0f);
	ApplyEffectToSelf(InitialSecondaryEffectClass,1.0f);
	ApplyEffectToSelf(InitialVitalEffectClass,1.0f);
}

FVector AXBaseCharacter::GetSocketLocation()
{
	check(WeaponMesh);
	return WeaponMesh->GetSocketLocation(WeaponTipSocketName);
}

void AXBaseCharacter::AddCharacterAbilities()
{
	//Only grate in Server
	if(!HasAuthority()) return;
	UXAbilitySystemComponent* XASC = CastChecked<UXAbilitySystemComponent>(AbilitySystemComponent);
	XASC->AddGameplayAbilities(StartGameplayAbilities);
}


