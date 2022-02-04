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

void AItem::Attach(UStaticMeshComponent* Parent, const FName& SocketName)
{
	// Important to disable before attachment
	StaticMeshComponent->SetSimulatePhysics(false);
	AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void AItem::Detach()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMeshComponent->SetSimulatePhysics(true);
}
