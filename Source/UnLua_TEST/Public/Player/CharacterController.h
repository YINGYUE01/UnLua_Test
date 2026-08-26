// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class UInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class UNLUA_TEST_API ACharacterController : public APlayerController
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
	
	UPROPERTY(EditAnywhere, Category = "Input")
	float SprintSpeed = 600.f;

	/** 松开冲刺后，MaxWalkSpeed 过渡回走路速度所需时间（秒） */
	UPROPERTY(EditAnywhere, Category = "Input", meta = (ClampMin = "0.01"))
	float SprintStopDuration = 0.4f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	void Look(const FInputActionValue& InputActionValue);
	void Move(const FInputActionValue& InputActionValue);
	void JumpStarted(const FInputActionValue& InputActionValue);
	void JumpCompleted(const FInputActionValue& InputActionValue);
	void ShiftMoveStarted(const FInputActionValue& InputActionValue);
	void ShiftMoveCompleted(const FInputActionValue& InputActionValue);

	void UpdateSprintSpeedBlend(float DeltaSeconds);

private:

	void AbilityInputTagPresses(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	float DefaultWalkSpeed = 0.f;
	float SpeedBlendElapsed = 0.f;
	float SpeedBlendStart = 0.f;
	bool bIsSprinting = false;
	bool bIsDeceleratingFromSprint = false;
};



