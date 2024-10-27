// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerController.generated.h"

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

private:
	//Move
	void Move(const struct FInputActionValue& InputActionValue);

	//检测鼠标下的Actor
	void CursorTrace();
};
