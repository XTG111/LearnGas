// Fill out your copyright notice in the Description page of Project Settings.


#include "XAssetManager.h"
#include "XGameplayTags.h"

UXAssetManager& UXAssetManager::Get()
{
	check(GEngine);
	UXAssetManager* XAssetManager = Cast<UXAssetManager>(GEngine->AssetManager);

	return *XAssetManager;
}

void UXAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//initialize native gameplay tags
	XGameplayTags::InitializeNativeGameplayTags();
}
