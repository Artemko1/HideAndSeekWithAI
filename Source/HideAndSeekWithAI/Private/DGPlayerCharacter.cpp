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

	PlayerInputComponent->BindAction("TryPickupItem", IE_Pressed, this, &ADGPlayerCharacter::TryPickupItem);
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &ADGPlayerCharacter::DropItem);

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

void ADGPlayerCharacter::TryPickupItem()
{
	const auto MyController = GetController();
	if (!MyController || HeldItem || !GetWorld())
	{
		return;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	MyController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FVector LookDirection = ViewRotation.Vector();
	const FVector EndOffset = LookDirection * ItemPickupRange;
	const FVector TraceEnd = ViewLocation + EndOffset;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility, CollisionParams);

	if (!HitResult.bBlockingHit)
	{
		return;
	}

	AItem* HitItem = Cast<AItem>(HitResult.GetActor());

	if (!HitItem)
	{
		return;
	}

	PickupItem(HitItem);
}
