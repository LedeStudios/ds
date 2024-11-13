// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "NonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DS_API ANonPlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	ANonPlayerCharacter();

protected:
	virtual void BeginPlay() override;
	
};
