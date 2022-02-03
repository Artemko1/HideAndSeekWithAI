// Fill out your copyright notice in the Description page of Project Settings.


#include "DGPlayerCharacter.h"

#include "DGCoreTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ADGPlayerCharacter::ADGPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(CameraComponent)
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 50.f));
	CameraComponent->bUsePawnControlRotation = true;

	ADGCharacter::SetGenericTeamId(FGenericTeamId(static_cast<uint8>(EDGTeams::Players)));
}

void ADGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(InputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADGPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADGPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ADGPlayerCharacter::MoveForward(const float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADGPlayerCharacter::MoveRight(const float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}
