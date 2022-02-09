// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox.h"

#include "Components/BoxComponent.h"
#include "Kismet/ImportanceSamplingLibrary.h"

ASpawnBox::ASpawnBox()
{
	PrimaryActorTick.bCanEverTick = false;

	AreaBox = CreateDefaultSubobject<UBoxComponent>("AreaBox");
	SetRootComponent(AreaBox);
	AreaBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpawnBox::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnBox::InitializeBounds()
{
	if (IsInitialized) { return; }
	IsInitialized = true;

	Index++;
	PrevValue = FVector2D(FMath::FRand(), FMath::FRand());

	const FVector Loc = GetActorLocation();
	check(AreaBox);
	const FVector Extent = AreaBox->GetUnscaledBoxExtent();

	XBoxLocationVector = FVector2D(Loc.X - Extent.X, Loc.X + Extent.X);
	YBoxLocationVector = FVector2D(Loc.Y - Extent.Y, Loc.Y + Extent.Y);
}

FVector2D ASpawnBox::GetNextRandomPoint2D()
{
	if (!IsInitialized) return FVector2D();

	const float NextX = UImportanceSamplingLibrary::NextSobolFloat(Index, 1, PrevValue.X);
	const float NextY = UImportanceSamplingLibrary::NextSobolFloat(Index, 2, PrevValue.Y);

	Index++;
	PrevValue.X = NextX;
	PrevValue.Y = NextY;

	const float LocationX = FMath::Lerp(XBoxLocationVector.X, XBoxLocationVector.Y, NextX);
	const float LocationY = FMath::Lerp(YBoxLocationVector.X, YBoxLocationVector.Y, NextY);

	return FVector2D(LocationX, LocationY);
}
