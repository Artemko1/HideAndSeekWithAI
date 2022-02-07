// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	check(StaticMeshComponent)
	SetRootComponent(StaticMeshComponent);

	StaticMeshComponent->SetSimulatePhysics(true);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

bool AItem::Attach(UStaticMeshComponent* Parent, const FName& SocketName)
{
	if (IsAttached)
	{
		return false;
	}

	// Important to disable before attachment
	StaticMeshComponent->SetSimulatePhysics(false);
	AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	IsAttached = true;
	return true;
}

bool AItem::Detach(AController* InstigatorController)
{
	if (!IsAttached)
	{
		return false;
	}

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMeshComponent->SetSimulatePhysics(true);
	IsAttached = false;

	bIsDroppedByPlayer = InstigatorController != nullptr && InstigatorController->IsPlayerController() ? true : false;

	return true;
}

void AItem::AddImpulse(const float Force) const
{
	// Reference values are from 600 to 3000 for 1m to 15m throw 
	StaticMeshComponent->AddImpulse(GetActorForwardVector() * Force, NAME_None, true);
}
