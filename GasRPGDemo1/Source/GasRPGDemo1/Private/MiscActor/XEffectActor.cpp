// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscActor/XEffectActor.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystems/XAttributeSet.h>

AXEffectActor::AXEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	
}

void AXEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UAbilitySystemInterface>())
	{
		IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
		const UXAttributeSet* XAttributeSet = Cast<UXAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(
				UXAttributeSet::StaticClass()
			)
		);
		//Just For test use const_cast
		UXAttributeSet* MutableXAttributeSet = const_cast<UXAttributeSet*>(XAttributeSet);
		MutableXAttributeSet->SetHealth(XAttributeSet->GetHealth() - 50.0f);
		MutableXAttributeSet->SetMana(XAttributeSet->GetMana() - 10.0f);
		Destroy();
	}
}

void AXEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AXEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AXEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AXEffectActor::EndOverlap);
}

