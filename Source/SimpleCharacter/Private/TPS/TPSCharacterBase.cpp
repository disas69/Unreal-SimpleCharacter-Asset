// Eugene Esaulenko, All Rights Reserved.

#include "TPS/TPSCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPS/TPSInputConfig.h"

ATPSCharacterBase::ATPSCharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Setup character movement
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;

    // Setup camera
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->TargetArmLength = 400.0f;
    SpringArmComponent->TargetOffset = FVector(0.0f, 0.0f, 60.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->bUsePawnControlRotation = false;
}

void ATPSCharacterBase::BeginPlay()
{
    Super::BeginPlay();
}

void ATPSCharacterBase::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // Get the forward direction based on the camera orientation and apply movement
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, MovementVector.Y);

    // Get the right direction based on the camera orientation and apply movement
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

void ATPSCharacterBase::Rotate(const FInputActionValue& Value)
{
    const FVector2D RotateAxisVector = Value.Get<FVector2D>();

    const float TurnAmount = RotateAxisVector.X * CameraMovementRate * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(TurnAmount);

    const float LookAmount = RotateAxisVector.Y * CameraMovementRate * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(LookAmount);
}

void ATPSCharacterBase::Jump(const FInputActionValue& Value)
{
    Super::Jump();
}

void ATPSCharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATPSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Add mapping context
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);

    // Bind actions
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    Input->BindAction(InputConfig->MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacterBase::Move);
    Input->BindAction(InputConfig->RotateAction, ETriggerEvent::Triggered, this, &ATPSCharacterBase::Rotate);
    Input->BindAction(InputConfig->JumpAction, ETriggerEvent::Triggered, this, &ATPSCharacterBase::Jump);
}
