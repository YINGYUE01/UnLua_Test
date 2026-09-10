// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UGameplayAbility;
class UMalGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class UNLUA_TEST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PossessedBy(AController* NewController) override;
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect);
	void InitializeAttributes();
	void InitializeAbilities();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="PrimaryAttribute")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	UPROPERTY(EditAnywhere,Category="SecondaryAttribute")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	UPROPERTY(EditAnywhere,Category="VitalAttribute")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>	AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility> > StartupAbilities;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
