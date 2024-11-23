// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/XProjectileSpell.h"

#include "Interaction/XCombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MiscActor/XProjectile.h"

void UXProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//UKismetSystemLibrary::PrintString(this, FString(TEXT("ActivateAbility cpp")), true, true,FColor::Yellow,3.0f);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if(!bIsServer) return;

	IXCombatInterface* CombatInterface =  Cast<IXCombatInterface>(GetAvatarActorFromActorInfo());
	if(CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetSocketLocation();
		FTransform SpawnTransform;

		//rotation
		
		SpawnTransform.SetLocation(SocketLocation);
		AXProjectile* Projectile = GetWorld()->SpawnActorDeferred<AXProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//give the projectile the gameplay effect for causing damage
		if(Projectile)	Projectile->FinishSpawning(SpawnTransform);
	}
	
}
