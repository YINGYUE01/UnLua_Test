// Fill out your copyright notice in the Description page of Project Settings.
#include "UnLua_TEST/Public/Character/CharacterBase.h"

#include "Character/SprintCharacterMovementComponent.h"
#include "Player/MalPlayerState.h"

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USprintCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AMalPlayerState* PS = Cast<AMalPlayerState>(GetController()->PlayerState);
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS,this);
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AttributeSet = PS->GetAttribute();
	}
	InitializeAttributes();
	InitializeAbilities();
}

void ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect)
{
	if (IsValid(Effect) && IsValid(GetAbilitySystemComponent()))
	{
		FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(Effect,1,ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
	}
}

void ACharacterBase::InitializeAttributes()
{
	ApplyEffectToSelf(PrimaryAttributes);
	ApplyEffectToSelf(SecondaryAttributes);
}

void ACharacterBase::InitializeAbilities()
{
	if (IsValid(AbilitySystemComponent))
	{
		UMalAbilitySystemComponent* MalASC = Cast<UMalAbilitySystemComponent>(AbilitySystemComponent);
		MalASC->AddCharacterAbilities(StartupAbilities);	
	}
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
