#include "Movement/SprintCharacterMovementComponent.h"

#include "GameFramework/Character.h"

class FSavedMove_Sprint final : public FSavedMove_Character
{
public:
	using Super = FSavedMove_Character;

	uint8 bSavedWantsToSprint : 1;

	virtual void Clear() override
	{
		Super::Clear();
		bSavedWantsToSprint = false;
	}

	virtual uint8 GetCompressedFlags() const override
	{
		return Super::GetCompressedFlags() | (bSavedWantsToSprint ? FLAG_Custom_0 : 0);
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
		bSavedWantsToSprint = static_cast<USprintCharacterMovementComponent*>(Character->GetCharacterMovement())->bWantsToSprint;
	}

	virtual void PrepMoveFor(ACharacter* Character) override
	{
		Super::PrepMoveFor(Character);
		static_cast<USprintCharacterMovementComponent*>(Character->GetCharacterMovement())->SetWantsToSprint(bSavedWantsToSprint);
	}
};

class FNetworkPredictionData_Client_Sprint final : public FNetworkPredictionData_Client_Character
{
public:
	using Super = FNetworkPredictionData_Client_Character;

	explicit FNetworkPredictionData_Client_Sprint(const UCharacterMovementComponent& ClientMovement)
		: Super(ClientMovement)
	{
	}

	virtual FSavedMovePtr AllocateNewMove() override
	{
		return FSavedMovePtr(new FSavedMove_Sprint());
	}
};

USprintCharacterMovementComponent::USprintCharacterMovementComponent()
	: bWantsToSprint(false)
{
}

void USprintCharacterMovementComponent::SetWantsToSprint(bool bNewWantsToSprint)
{
	bWantsToSprint = bNewWantsToSprint;
}

float USprintCharacterMovementComponent::GetMaxSpeed() const
{
	return bWantsToSprint && IsMovingOnGround() ? SprintSpeed : Super::GetMaxSpeed();
}

void USprintCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
	bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

FNetworkPredictionData_Client* USprintCharacterMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		USprintCharacterMovementComponent* MutableThis = const_cast<USprintCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Sprint(*this);
	}

	return ClientPredictionData;
}
