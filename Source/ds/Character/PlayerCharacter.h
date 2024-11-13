// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

class UInventoryComponent;

UCLASS()
class DS_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	
// ======================================================================================
//  Unreal Engine Overrides
// ======================================================================================
protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	

};
