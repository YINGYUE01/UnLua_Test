// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"

class UInputAction;
/**
 * 
 */
USTRUCT()
struct FAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction;
	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag;
};

UCLASS()
class UNLUA_TEST_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	TArray<FAction> Actions;
	FAction* GetActionByTag(const FGameplayTag& Tag);
};
