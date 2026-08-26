// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "Input/ULEnhancedInputComponent.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	UEnhancedInputLocalPlayerSubsystem* LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalSubsystem)
	{
		LocalSubsystem->AddMappingContext(PlayerContext, 0);
	}
}

void ACharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateSprintSpeedBlend(DeltaSeconds);
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

void ACharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const ACharacter* MyCharacter = Cast<ACharacter>(InPawn))
	{
		if (const UCharacterMovementComponent* Movement = MyCharacter->GetCharacterMovement())
		{
			DefaultWalkSpeed = Movement->MaxWalkSpeed;
		}
		bIsSprinting = false;
		bIsDeceleratingFromSprint = false;
		SpeedBlendElapsed = 0.f;
	}
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
	ACharacter* MyCharacter = GetPawn<ACharacter>();
	if (!MyCharacter)
	{
		return;
	}

	if (UCharacterMovementComponent* Movement = MyCharacter->GetCharacterMovement())
	{
		bIsSprinting = true;
		bIsDeceleratingFromSprint = false;
		SpeedBlendElapsed = 0.f;
		Movement->MaxWalkSpeed = SprintSpeed;
	}
}

void ACharacterController::ShiftMoveCompleted(const FInputActionValue& InputActionValue)
{
	(void)InputActionValue;
	ACharacter* MyCharacter = GetPawn<ACharacter>();
	if (!MyCharacter)
	{
		return;
	}

	if (UCharacterMovementComponent* Movement = MyCharacter->GetCharacterMovement())
	{
		bIsSprinting = false;
		bIsDeceleratingFromSprint = true;
		SpeedBlendElapsed = 0.f;
		SpeedBlendStart = Movement->MaxWalkSpeed;
	}
}

void ACharacterController::UpdateSprintSpeedBlend(float DeltaSeconds)
{
	if (!bIsDeceleratingFromSprint || bIsSprinting)
	{
		return;
	}

	ACharacter* MyCharacter = GetPawn<ACharacter>();
	if (!MyCharacter)
	{
		return;
	}

	UCharacterMovementComponent* Movement = MyCharacter->GetCharacterMovement();
	if (!Movement)
	{
		return;
	}
	SpeedBlendElapsed += DeltaSeconds;
	const float Duration = FMath::Max(SprintStopDuration, KINDA_SMALL_NUMBER);
	const float Alpha = FMath::Clamp(SpeedBlendElapsed / Duration, 0.f, 1.f);
	Movement->MaxWalkSpeed = FMath::InterpEaseInOut(SpeedBlendStart, DefaultWalkSpeed, Alpha, 2.f);

	if (Alpha >= 1.f)
	{
		Movement->MaxWalkSpeed = DefaultWalkSpeed;
		bIsDeceleratingFromSprint = false;
	}
}


void ACharacterController::AbilityInputTagPresses(FGameplayTag InputTag)
{
	
}

void ACharacterController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
}

void ACharacterController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
}