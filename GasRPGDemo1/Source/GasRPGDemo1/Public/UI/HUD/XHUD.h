// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "XHUD.generated.h"

class UXUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API AXHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UXUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* pc,APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as);
	
private:
	UPROPERTY(EditAnywhere,Category="Overlay")
	TSubclassOf<UXUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere,Category="Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
