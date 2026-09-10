#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SprintCharacterMovementComponent.generated.h"

/**
 * Character movement with a sprint flag carried by CharacterMovement's saved moves.
 * This keeps client prediction and server simulation on the same movement speed.
 */
UCLASS()
class UNLUA_TEST_API USprintCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	void SetSprinting(bool bNewWantsToSprint);
	bool IsSprinting() const { return bWantsToSprint; }

	virtual float GetMaxSpeed() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement|Sprint", meta = (ClampMin = "0.0"))
	float SprintSpeed = 600.f;

private:
	uint8 bWantsToSprint : 1;
};
