// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DGAICharacter.h"

#include "AI/DGAIController.h"
#include "DGCoreTypes.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADGAICharacter::ADGAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Чек возможно глупый, но я добавил их везде, когда искал причину краша (причина была в DGTurnBTTaskNode, там описано)
	check(GetCapsuleComponent())
	GetCapsuleComponent()->InitCapsuleSize(25.f, 50.0f);

	AIControllerClass = ADGAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	ADGCharacter::SetGenericTeamId(FGenericTeamId(static_cast<uint8>(EDGTeams::Bots)));

	bUseControllerRotationYaw = false;

	check(GetCharacterMovement())
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ADGAICharacter::SetMovementMode(const EDGMovementSpeedMode DGMovementSpeedMode)
{
	if (MovementMultipliers.Contains(DGMovementSpeedMode))
	{
		SetMaxSpeed(GetBaseSpeed() * MovementMultipliers[DGMovementSpeedMode]);
	}
	else
	{
		SetMaxSpeed(GetBaseSpeed());
	}
}

void ADGAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (MovementMultipliers.Contains(EDGMovementSpeedMode::Default))
	{
		SetMaxSpeed(GetBaseSpeed() * MovementMultipliers[EDGMovementSpeedMode::Default]);
	}
}
