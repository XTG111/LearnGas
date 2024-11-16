// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "XHUD.generated.h"

class UXAttributeMenuWidgetController;
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
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* pc,APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as);

	UXAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
private:
	UPROPERTY()
	TObjectPtr<UXUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere,Category="Overlay")
	TSubclassOf<UXUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere,Category="Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UXAttributeMenuWidgetController> AttributesMenuWidgetController;
	UPROPERTY(EditAnywhere,Category="AttributesMenu")
	TSubclassOf<UXAttributeMenuWidgetController> AttributesMenuWidgetControllerClass;
};
