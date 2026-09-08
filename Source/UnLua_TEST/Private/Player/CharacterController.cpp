// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystem/CharacterAbilitySystemComponent.h"
#include "Character/MyCharacter.h"
#include "Input/ULEnhancedInputComponent.h"
#include "Movement/SprintCharacterMovementComponent.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalSubsystem)
	{
		LocalSubsystem->AddMappingContext(PlayerContext, 0);
	}
}

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}

	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterController::Move);
	}
	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterController::Look);
	}
	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacterController::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacterController::JumpCompleted);
	}
	if (ShiftAction)
	{
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ACharacterController::ShiftMoveStarted);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ACharacterController::ShiftMoveCompleted);
	}

	if (UULEnhancedInputComponent* ULInputComponent = Cast<UULEnhancedInputComponent>(EnhancedInputComponent))
	{
		if (InputConfig)
		{
			ULInputComponent->BindAbilityActions(InputConfig,
				this,
				&ACharacterController::AbilityInputTagPresses,
				&ACharacterController::AbilityInputTagReleased,
				&ACharacterController::AbilityInputTagHeld);
		}
	}
}

UCharacterAbilitySystemComponent* ACharacterController::GetASC()
{
	if (ASC==nullptr)
	{
		//TODO 更换为接口获取ASC
		ASC = Cast<UCharacterAbilitySystemComponent>(Cast<AMyCharacter>(GetPawn())->GetAbilitySystemComponent());
	}
	return ASC;
}

void ACharacterController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxis = InputActionValue.Get<FVector2D>();
	AddYawInput(LookAxis.X);
	AddPitchInput(LookAxis.Y);
}

void ACharacterController::Move(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	const FVector2D InputAxis = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn->AddMovementInput(ForwardDirection, InputAxis.Y);
	ControlledPawn->AddMovementInput(RightDirection, InputAxis.X);
}

void ACharacterController::JumpStarted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	if (ACharacter* MyCharacter = GetPawn<ACharacter>())
	{
		MyCharacter->Jump();
	}
}

void ACharacterController::JumpCompleted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	if (ACharacter* MyCharacter = GetPawn<ACharacter>())
	{
		MyCharacter->StopJumping();
	}
}

void ACharacterController::ShiftMoveStarted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	SetSprinting(true);
}

void ACharacterController::ShiftMoveCompleted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	SetSprinting(false);
}

void ACharacterController::SetSprinting(bool bNewIsSprinting)
{
	ACharacter* MyCharacter = GetPawn<ACharacter>();
	if (!MyCharacter)
	{
		return;
	}

	if (USprintCharacterMovementComponent* Movement = Cast<USprintCharacterMovementComponent>(MyCharacter->GetCharacterMovement()))
	{
		Movement->SprintSpeed = SprintSpeed;
		Movement->SetWantsToSprint(bNewIsSprinting);
	}
}


void ACharacterController::AbilityInputTagPresses(FGameplayTag InputTag)
{
	if (HasAuthority() && InputTag.IsValid())
	{
		if (GetASC())
		{
			GetASC()->AbilityInputPressed(InputTag);
		}
	}
}

void ACharacterController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (HasAuthority() && InputTag.IsValid())
	{
		if (GetASC())
		{
			GetASC()->AbilityInputReleased(InputTag);
		}
	}
}

void ACharacterController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (HasAuthority() && InputTag.IsValid())
	{
		if (GetASC())
		{
			GetASC()->AbilityInputHeld(InputTag);
		}
	}
	
}
