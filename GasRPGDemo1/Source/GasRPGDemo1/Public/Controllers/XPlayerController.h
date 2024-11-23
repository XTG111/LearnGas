// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerController.generated.h"

class USplineComponent;
class UXInputConfigDataAsset;
class UXAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AXPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> XPlayerContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;
	//记录前后两次鼠标检测的Actor
	TScriptInterface<class IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> CurActor;
	FHitResult VisibilityCursorHit;

	//GA-InputAction
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UXInputConfigDataAsset> InputConfig;

	UPROPERTY()
	TObjectPtr<UXAbilitySystemComponent> XAbilitySystemComponent;

private:
	//Move
	void Move(const struct FInputActionValue& InputActionValue);
	//检测鼠标下的Actor
	void CursorTrace();
	//Pressed
	void PressedFunc(FGameplayTag GameplayTag);
	//Released
	void ReleasedFunc(FGameplayTag GameplayTag);
	//Held
	void HeldFunc(FGameplayTag GameplayTag);

	UXAbilitySystemComponent* GetXASC();

	//this bool param use for choose run or activate ability, because we use the left mouse button
	//if CurActor!=nullptr we can say we need activate the ability, but if not we can run
	bool bTarget = false;
	
	//click To Move params
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.0f; //the left mouse button held time
	float ShortPressThreshold = 0.5f; // the least time to check held
	bool bAutoRunning = false;
	UPROPERTY(EditDefaultsOnly, Category = "Click Move")
	float AutoRunAcceptanceRadius = 50.f;
	UPROPERTY(VisibleAnywhere, Category = "Click Move")
	TObjectPtr<USplineComponent> Spline; // use for move trace

	//click to move func
	void AutoRun();
};
