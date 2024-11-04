// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XBaseCharacter.h"

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

