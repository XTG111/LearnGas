// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XEnemyCharacter.h"
#include "AbilitySystems/XAbilitySystemComponent.h"
#include "AbilitySystems/XAttributeSet.h"
#include "../GasRPGDemo1.h"


AXEnemyCharacter::AXEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UXAbilitySystemComponent>(TEXT("EnemyAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UXAttributeSet>(TEXT("EnemyAttributeSet"));
}

void AXEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AXEnemyCharacter::HighlightActor()
{
	//UE_LOG(LogTemp, Warning, TEXT("HighlightActor"));
	//bHighlight = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(true);
		WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AXEnemyCharacter::UnHighlightActor()
{
	///UE_LOG(LogTemp, Warning, TEXT("UnHighlightActor"));
	//bHighlight = false;
	GetMesh()->SetRenderCustomDepth(false);
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(false);
	}
}
