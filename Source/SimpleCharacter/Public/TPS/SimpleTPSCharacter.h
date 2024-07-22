// Eugene Esaulenko, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleTPSCharacter.generated.h"

UCLASS()
class SIMPLECHARACTER_API ASimpleTPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASimpleTPSCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;
};
