// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MalGameplayAbility.generated.h"


USTRUCT()
struct FDamageContext
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float BaseDamage;
};

/**
 * 
 */
UCLASS()
class UNLUA_TEST_API UMalGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FGameplayTag StartInputTag = FGameplayTag();
	UPROPERTY(EditAnywhere)
	FDamageContext DamageContext;
	
};
