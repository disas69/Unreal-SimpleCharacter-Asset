// Eugene Esaulenko, All Rights Reserved.

#include "TPBaseCharacter.h"
#include "InputConfig.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATPBaseCharacter::ATPBaseCharacter()
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

void ATPBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATPBaseCharacter::Move(const FInputActionValue& Value)
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

void ATPBaseCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    const float TurnAmount = LookAxisVector.X * CameraMovementRate * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(TurnAmount);

    const float LookAmount = LookAxisVector.Y * CameraMovementRate * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(LookAmount);
}

void ATPBaseCharacter::Jump(const FInputActionValue& Value)
{
    Super::Jump();
}

void ATPBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Add mapping context
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);

    // Bind actions
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    Input->BindAction(InputConfig->MoveAction, ETriggerEvent::Triggered, this, &ATPBaseCharacter::Move);
    Input->BindAction(InputConfig->LookAction, ETriggerEvent::Triggered, this, &ATPBaseCharacter::Look);
    Input->BindAction(InputConfig->JumpAction, ETriggerEvent::Triggered, this, &ATPBaseCharacter::Jump);
}
