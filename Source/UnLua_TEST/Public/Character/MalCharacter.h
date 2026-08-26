
#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MalCharacter.generated.h"


UCLASS()
class UNLUA_TEST_API AMalCharacter : public AMyCharacter
{
public:
	GENERATED_BODY()
	virtual void BeginPlay();
protected:

private:
	
};
