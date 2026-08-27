// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputInfo.generated.h"
class UMalGameplayAbility;

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMalGameplayAbility> Ability;
};

/**
 * 
 */
UCLASS()
class UNLUA_TEST_API UInputInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FAbilityInfo> Abilities;
};
