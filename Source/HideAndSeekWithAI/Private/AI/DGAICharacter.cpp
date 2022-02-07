// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DGAICharacter.h"

#include "AI/DGAIController.h"
#include "DGCoreTypes.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADGAICharacter::ADGAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	check(GetCapsuleComponent())
	GetCapsuleComponent()->InitCapsuleSize(25.f, 50.0f);

	AIControllerClass = ADGAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	ADGCharacter::SetGenericTeamId(FGenericTeamId(static_cast<uint8>(EDGTeams::Bots)));

	bUseControllerRotationYaw = false;

	check(GetCharacterMovement())
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ADGAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
