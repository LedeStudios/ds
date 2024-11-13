// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class DS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	
// ======================================================================================
//  Handle Inputs
// ======================================================================================
public:
	UFUNCTION(BlueprintCallable, Category="DS")
	virtual void HandleMovementInput(const FVector2D& Input);

	UFUNCTION(BlueprintCallable, Category="DS")
	virtual void HandleCameraInput(const FVector2D& Input);
	
};
