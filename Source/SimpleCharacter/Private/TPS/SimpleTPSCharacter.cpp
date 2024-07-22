// Eugene Esaulenko, All Rights Reserved.

#include "TPS/SimpleTPSCharacter.h"

ASimpleTPSCharacter::ASimpleTPSCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASimpleTPSCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ASimpleTPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASimpleTPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
