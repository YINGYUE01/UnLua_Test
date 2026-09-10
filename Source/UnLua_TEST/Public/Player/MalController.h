// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "MalController.generated.h"

class UMalAbilitySystemComponent;
class UInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class UNLUA_TEST_API AMalController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputConfig> InputConfig;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	TObjectPtr<UMalAbilitySystemComponent> ASC;
	UMalAbilitySystemComponent* GetASC();

	void Look(const FInputActionValue& InputActionValue);
	void Move(const FInputActionValue& InputActionValue);
	void JumpStarted(const FInputActionValue& InputActionValue);
	void JumpCompleted(const FInputActionValue& InputActionValue);
	void ShiftMoveStarted(const FInputActionValue& InputActionValue);
	void ShiftMoveCompleted(const FInputActionValue& InputActionValue);

private:

	void AbilityInputTagPresses(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
};


