// Fill out your copyright notice in the Description page of Project Settings.


#include "DGCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


ADGCharacter::ADGCharacter(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.DoNotCreateDefaultSubobject(MeshComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(25.f, 50.0f);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetCapsuleComponent());
	StaticMeshComponent->SetOwnerNoSee(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetMaxSpeed();
}

void ADGCharacter::SetMaxSpeed() const
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * BaseSpeedMultiplier;
	}
}
