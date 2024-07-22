// Eugene Esaulenko, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"

class UInputAction;

UCLASS()
class SIMPLECHARACTER_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MoveAction = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* LookAction = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* JumpAction = nullptr;
};
