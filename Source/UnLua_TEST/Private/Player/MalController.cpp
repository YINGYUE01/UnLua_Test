// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MalController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "AbilitySystem/MalAbilitySystemComponent.h"
#include "Character/CharacterBase.h"
#include "Character/SprintCharacterMovementComponent.h"
#include "Input/ULEnhancedInputComponent.h"

void AMalController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	UEnhancedInputLocalPlayerSubsystem* LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalSubsystem)
	{
		LocalSubsystem->AddMappingContext(PlayerContext, 0);
	}
}

void AMalController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}

	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMalController::Move);
	}
	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMalController::Look);
	}
	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMalController::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMalController::JumpCompleted);
	}
	if (ShiftAction)
	{
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AMalController::ShiftMoveStarted);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AMalController::ShiftMoveCompleted);
	}

	if (UULEnhancedInputComponent* ULInputComponent = Cast<UULEnhancedInputComponent>(EnhancedInputComponent))
	{
		if (InputConfig)
		{
			ULInputComponent->BindAbilityActions(InputConfig,
				this,
				&AMalController::AbilityInputTagPresses,
				&AMalController::AbilityInputTagReleased,
				&AMalController::AbilityInputTagHeld);
		}
	}
}

void AMalController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

UMalAbilitySystemComponent* AMalController::GetASC()
{
	if (ASC==nullptr)
	{
		//TODO 更换为接口获取ASC
		ASC = Cast<UMalAbilitySystemComponent>(Cast<ACharacterBase>(GetPawn())->GetAbilitySystemComponent());
	}
	return ASC;
}

void AMalController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxis = InputActionValue.Get<FVector2D>();
	AddYawInput(LookAxis.X);
	AddPitchInput(LookAxis.Y);
}

void AMalController::Move(const FInputActionValue& InputActionValue)
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

void AMalController::JumpStarted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	if (ACharacter* MyCharacter = GetPawn<ACharacter>())
	{
		MyCharacter->Jump();
	}
}

void AMalController::JumpCompleted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	if (ACharacter* MyCharacter = GetPawn<ACharacter>())
	{
		MyCharacter->StopJumping();
	}
}

void AMalController::ShiftMoveStarted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	ACharacter* MyCharacter = GetPawn<ACharacter>();
	if (!MyCharacter)
	{
		return;
	}

	if (USprintCharacterMovementComponent* Movement = Cast<USprintCharacterMovementComponent>(MyCharacter->GetCharacterMovement()))
	{
		Movement->SetSprinting(true);
	}
}

void AMalController::ShiftMoveCompleted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	ACharacter* MyCharacter = GetPawn<ACharacter>();
	if (!MyCharacter)
	{
		return;
	}

	if (USprintCharacterMovementComponent* Movement = Cast<USprintCharacterMovementComponent>(MyCharacter->GetCharacterMovement()))
	{
		Movement->SetSprinting(false);
	}
}


void AMalController::AbilityInputTagPresses(FGameplayTag InputTag)
{
	if (HasAuthority() && InputTag.IsValid())
	{
		if (GetASC())
		{
			GetASC()->AbilityInputPressed(InputTag);
		}
	}
}

void AMalController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (HasAuthority() && InputTag.IsValid())
	{
		if (GetASC())
		{
			GetASC()->AbilityInputReleased(InputTag);
		}
	}
}

void AMalController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (HasAuthority() && InputTag.IsValid())
	{
		if (GetASC())
		{
			GetASC()->AbilityInputHeld(InputTag);
		}
	}
	
}
