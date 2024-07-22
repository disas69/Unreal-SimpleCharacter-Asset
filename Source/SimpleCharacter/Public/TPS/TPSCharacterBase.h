// Eugene Esaulenko, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "TPSCharacterBase.generated.h"

class UTPSInputConfig;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SIMPLECHARACTER_API ATPSCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ATPSCharacterBase();

    USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
    UCameraComponent* GetCameraComponent() const { return CameraComponent; }

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArmComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* CameraComponent = nullptr;

    // Properties
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputMappingContext* InputMappingContext = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UTPSInputConfig* InputConfig = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float CameraMovementRate = 60.0f;

    virtual void BeginPlay() override;
    virtual void Move(const FInputActionValue& Value);
    virtual void Rotate(const FInputActionValue& Value);
    virtual void Jump(const FInputActionValue& Value);
};
