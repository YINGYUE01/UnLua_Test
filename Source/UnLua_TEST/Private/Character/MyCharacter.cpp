// Fill out your copyright notice in the Description page of Project Settings.
#include "UnLua_TEST/Public/Character/MyCharacter.h"

#include "Movement/SprintCharacterMovementComponent.h"
#include "Player/CharacterPlayerState.h"

AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USprintCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ACharacterPlayerState* PS = Cast<ACharacterPlayerState>(GetController()->PlayerState);
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS,this);
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AttributeSet = PS->GetAttribute();
	}
	InitializeAttributes();
	InitializeAbilities();
}

void AMyCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect)
{
	if (IsValid(Effect) && IsValid(GetAbilitySystemComponent()))
	{
		FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(Effect,1,ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
	}
}

void AMyCharacter::InitializeAttributes()
{
	ApplyEffectToSelf(PrimaryAttributes);
	ApplyEffectToSelf(SecondaryAttributes);
}

void AMyCharacter::InitializeAbilities()
{
	if (IsValid(AbilitySystemComponent))
	{
		UCharacterAbilitySystemComponent* MalASC = Cast<UCharacterAbilitySystemComponent>(AbilitySystemComponent);
		MalASC->AddCharacterAbilities(StartupAbilities);	
	}
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
