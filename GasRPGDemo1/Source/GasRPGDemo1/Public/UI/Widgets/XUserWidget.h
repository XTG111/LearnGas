// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASRPGDEMO1_API UXUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	//After the SetWidgetController Call, Can use this func to know the controller Set Already  
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
