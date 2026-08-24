// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class UNLUA_TEST_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UFUNCTION(BlueprintImplementableEvent)
	void Look(const struct FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintImplementableEvent)
	void Jump(const struct FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintImplementableEvent)
	void Move(const struct FInputActionValue& InputActionValue);

private:
	virtual void BeginPlay() override;

};
