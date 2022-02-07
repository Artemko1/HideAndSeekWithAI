// Fill out your copyright notice in the Description page of Project Settings.


#include "DGFunctionLibrary.h"

#include "Kismet/KismetSystemLibrary.h"

AActor* UDGFunctionLibrary::GetNearestActor(const UObject* WorldContextObject, const FVector SpherePos, float SphereRadius,
                                            const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass* ActorClassFilter,
                                            const TArray<AActor*>& ActorsToIgnore)
{
	TArray<AActor*> OutActors;
	const bool Overlap = UKismetSystemLibrary::SphereOverlapActors(WorldContextObject, SpherePos, SphereRadius, ObjectTypes,
	                                                               ActorClassFilter, ActorsToIgnore, OutActors);
	if (!Overlap)
	{
		return nullptr;
	}

	float BestDistance = MAX_FLT;
	AActor* ClosestActor = nullptr;

	for (const auto OutActor : OutActors)
	{
		const auto CurrentDistance = FVector::Distance(OutActor->GetActorLocation(), SpherePos);
		if (CurrentDistance < BestDistance)
		{
			BestDistance = CurrentDistance;
			ClosestActor = OutActor;
		}
	}

	return ClosestActor;
}
