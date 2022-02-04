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

	SetMaxSpeed();
}

void ADGCharacter::PickupItem(AItem* Item)
{
	if (!Item || HeldItem)
	{
		return;
	}

	Item->Attach(StaticMeshComponent, ItemSocketName);
	HeldItem = Item;
}

void ADGCharacter::DropItem()
{
	if (!HeldItem)
	{
		return;
	}

	HeldItem->Detach();
	HeldItem = nullptr;
}

void ADGCharacter::ThrowItem()
{
}

void ADGCharacter::SetMaxSpeed() const
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * BaseSpeedMultiplier;
	}
}
