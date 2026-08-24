// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalSubsystem)
	{
		LocalSubsystem->AddMappingContext(PlayerContext,0);
	}
}

// void ACharacterController::Move(const struct FInputActionValue& InputActionValue)
// {
// 	const FRotator Rotation = GetControlRotation();
// 	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
// 	
// 	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
// 	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 	if (APawn* ControlledPawn = GetPawn<APawn>())
// 	{
// 		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
// 		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
// 	}
// }

