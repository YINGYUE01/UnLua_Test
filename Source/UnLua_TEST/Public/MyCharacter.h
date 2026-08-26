// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class UNLUA_TEST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect);
	void InitializeAttributes();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="PrimaryAttribute")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	UPROPERTY(EditAnywhere,Category="PrimalAttribute")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>	AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
