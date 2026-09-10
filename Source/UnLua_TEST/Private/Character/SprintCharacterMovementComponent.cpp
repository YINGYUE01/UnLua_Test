#include "Character/SprintCharacterMovementComponent.h"

#include "GameFramework/Character.h"

class FSavedMove_Sprint final : public FSavedMove_Character
{
public:
	using Super = FSavedMove_Character;

	uint8 bSavedWantsToSprint : 1;

	FSavedMove_Sprint()
		: bSavedWantsToSprint(false)
	{
	}

	virtual void Clear() override
	{
		Super::Clear();
		bSavedWantsToSprint = false;
	}

	virtual uint8 GetCompressedFlags() const override
	{
		uint8 Result = Super::GetCompressedFlags();
		if (bSavedWantsToSprint)
		{
			Result |= FLAG_Custom_0;
		}
		return Result;
	}

	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override
	{
		const FSavedMove_Sprint* NewSprintMove = static_cast<const FSavedMove_Sprint*>(NewMove.Get());
		if (bSavedWantsToSprint != NewSprintMove->bSavedWantsToSprint)
		{
			return false;
		}

		return Super::CanCombineWith(NewMove, Character, MaxDelta);
	}

	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, const FVector& NewAccel,
		FNetworkPredictionData_Client_Character& ClientData) override
	{
		Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

		const USprintCharacterMovementComponent* Movement =
			Cast<USprintCharacterMovementComponent>(Character->GetCharacterMovement());
		bSavedWantsToSprint = Movement && Movement->IsSprinting();
	}

	virtual void PrepMoveFor(ACharacter* Character) override
	{
		Super::PrepMoveFor(Character);

		if (USprintCharacterMovementComponent* Movement =
			Cast<USprintCharacterMovementComponent>(Character->GetCharacterMovement()))
		{
			Movement->SetSprinting(bSavedWantsToSprint);
		}
	}
};

class FNetworkPredictionData_Client_Sprint final : public FNetworkPredictionData_Client_Character
{
public:
	explicit FNetworkPredictionData_Client_Sprint(const UCharacterMovementComponent& ClientMovement)
		: Super(ClientMovement)
	{
	}

	virtual FSavedMovePtr AllocateNewMove() override
	{
		return FSavedMovePtr(new FSavedMove_Sprint());
	}
};

void USprintCharacterMovementComponent::SetSprinting(bool bNewWantsToSprint)
{
	bWantsToSprint = bNewWantsToSprint;
}

float USprintCharacterMovementComponent::GetMaxSpeed() const
{
	if (bWantsToSprint && IsMovingOnGround())
	{
		return SprintSpeed;
	}

	return Super::GetMaxSpeed();
}

void USprintCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
	bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

FNetworkPredictionData_Client* USprintCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr);

	if (ClientPredictionData == nullptr)
	{
		USprintCharacterMovementComponent* MutableThis = const_cast<USprintCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Sprint(*this);
	}

	return ClientPredictionData;
}
