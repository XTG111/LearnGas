// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/XUserWidget.h"

void UXUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
