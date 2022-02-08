// Fill out your copyright notice in the Description page of Project Settings.


#include "DGCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


ADGCharacter::ADGCharacter(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.DoNotCreateDefaultSubobject(MeshComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	check(GetCapsuleComponent())
	GetCapsuleComponent()->InitCapsuleSize(25.f, 50.0f);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	check(StaticMeshComponent)
	StaticMeshComponent->SetupAttachment(GetCapsuleComponent());
	StaticMeshComponent->SetOwnerNoSee(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADGCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetMaxSpeed(BaseSpeed);
}

void ADGCharacter::PickupItem(AItem* Item)
{
	if (!Item || IsHoldingItem())
	{
		return;
	}

	const bool Success = Item->Attach(StaticMeshComponent, ItemSocketName);
	if (Success)
	{
		HeldItem = Item;
	}
}

void ADGCharacter::DropItem()
{
	if (!IsHoldingItem())
	{
		return;
	}

	const bool Success = HeldItem->Detach(GetController());
	if (Success)
	{
		HeldItem = nullptr;
	}
}

void ADGCharacter::ThrowItem(const float Force)
{
	if (!IsHoldingItem())
	{
		return;
	}

	const bool Success = HeldItem->Detach(GetController());
	if (Success)
	{
		HeldItem->AddImpulse(Force);
		HeldItem = nullptr;
	}
}

bool ADGCharacter::GetItemSpawnLocation(FVector& OutLocation) const
{
	if (!HeldItem)
	{
		return false;
	}

	OutLocation = HeldItem->GetSpawnLocation();
	return true;
}

void ADGCharacter::SetMaxSpeed(const float Speed) const
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
}

float ADGCharacter::GetCurrentSpeed() const
{
	if (GetCharacterMovement())
	{
		return GetCharacterMovement()->MaxWalkSpeed;
	}

	return -1.f;
}
