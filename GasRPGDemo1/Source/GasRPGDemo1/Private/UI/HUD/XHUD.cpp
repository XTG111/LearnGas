// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/XHUD.h"
#include "UI/Widgets/XUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/XAttributeMenuWidgetController.h"

UOverlayWidgetController* AXHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//调用 绑定属性变化的函数, 将属性与变化逻辑进行绑定
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController; 
	}
	return OverlayWidgetController;
}

void AXHUD::InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as)
{
	//检测是否在编辑器中设置好了Overlay的Class
	checkf(OverlayWidgetClass, TEXT("Need Initialize the OverlayWidgetClass"));
	checkf(OverlayWidgetControllerClass, TEXT("Need Initialize the OverlayWidgetControllerClass"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UXUserWidget>(Widget);

	//设置UI的Controller
	const FWidgetControllerParams WidgetControllerParams(pc,ps,asc,as);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);

	//初始化UI上的Attribute显示
	WidgetController->BroadCastInitValue();
	
	Widget->AddToViewport();
}

UXAttributeMenuWidgetController* AXHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributesMenuWidgetController == nullptr)
	{
		AttributesMenuWidgetController = NewObject<UXAttributeMenuWidgetController>(this, AttributesMenuWidgetControllerClass);
		AttributesMenuWidgetController->SetWidgetControllerParams(WCParams);
		//调用 绑定属性变化的函数, 将属性与变化逻辑进行绑定
		AttributesMenuWidgetController->BindCallbacksToDependencies();
		return AttributesMenuWidgetController; 
	}
	return AttributesMenuWidgetController;
}

