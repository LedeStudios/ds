// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "Character/PlayerCharacter.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = CastChecked<APlayerCharacter>(GetCharacter());
}

void APlayerControllerBase::HandleMovementInput(const FVector2D& Input)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	PlayerCharacter->AddMovementInput(ForwardVector, Input.Y);
	PlayerCharacter->AddMovementInput(RightVector, Input.X);
}

void APlayerControllerBase::HandleCameraInput(const FVector2D& Input)
{
	PlayerCharacter->AddControllerPitchInput(Input.Y);
	PlayerCharacter->AddControllerYawInput(Input.X);
}