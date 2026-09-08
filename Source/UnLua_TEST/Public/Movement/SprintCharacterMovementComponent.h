#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SprintCharacterMovementComponent.generated.h"

class FSavedMove_Sprint;

UCLASS()
class UNLUA_TEST_API USprintCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0"))
	float SprintSpeed = 600.f;

	void SetWantsToSprint(bool bNewWantsToSprint);

	virtual float GetMaxSpeed() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;

private:
	friend class FSavedMove_Sprint;

	uint8 bWantsToSprint : 1 = false;
};
