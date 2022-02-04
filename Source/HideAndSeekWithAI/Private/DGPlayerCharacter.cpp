// Fill out your copyright notice in the Description page of Project Settings.


#include "DGPlayerCharacter.h"

#include "DGCoreTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogDGPlayerCharacter, Display, All);

ADGPlayerCharacter::ADGPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(CameraComponent)
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 50.f));
	CameraComponent->bUsePawnControlRotation = true;

	ADGCharacter::SetGenericTeamId(FGenericTeamId(static_cast<uint8>(EDGTeams::Players)));
}

void ADGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ItemMaxThrowForce < ItemMinThrowForce)
	{
		UE_LOG(LogDGPlayerCharacter, Warning, TEXT("ItemMaxThrowForce is less then ItemMinThrowForce"));
	}
}

void ADGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(InputComponent);

	PlayerInputComponent->BindAction("TryPickupItem", IE_Pressed, this, &ADGPlayerCharacter::TryPickupItem);
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &ADGPlayerCharacter::DropItem);
	PlayerInputComponent->BindAction("ThrowItem", IE_Pressed, this, &ADGPlayerCharacter::ChargeThrow);
	PlayerInputComponent->BindAction("ThrowItem", IE_Released, this, &ADGPlayerCharacter::ReleaseThrow);

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

void ADGPlayerCharacter::ChargeThrow()
{
	if (IsHoldingItem())
	{
		GetWorldTimerManager().SetTimer(ChargeThrowTimerHandle, this, &ADGPlayerCharacter::ReleaseThrow, ItemThrowMaxChargeTime, false);
	}
}

void ADGPlayerCharacter::ReleaseThrow()
{
	if (!IsHoldingItem() || !GetWorldTimerManager().IsTimerActive(ChargeThrowTimerHandle))
	{
		return;
	}

	const float ElapsedPercentTime = GetWorldTimerManager().GetTimerElapsed(ChargeThrowTimerHandle) / ItemThrowMaxChargeTime;
	GetWorldTimerManager().ClearTimer(ChargeThrowTimerHandle);

	const float ResultForce = FMath::Lerp(ItemMinThrowForce, ItemMaxThrowForce, ElapsedPercentTime);
	ThrowItem(ResultForce);
}

void ADGPlayerCharacter::TryPickupItem()
{
	const auto MyController = GetController();
	if (!MyController || IsHoldingItem() || !GetWorld())
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
