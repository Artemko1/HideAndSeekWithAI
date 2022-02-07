// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DGFunctionLibrary.generated.h"


UCLASS()
class HIDEANDSEEKWITHAI_API UDGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Collision",
		meta=(WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "GetNearestActor"))
	static AActor* GetNearestActor(const UObject* WorldContextObject, const FVector SpherePos, float SphereRadius,
	                               const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass* ActorClassFilter,
	                               const TArray<AActor*>& ActorsToIgnore);
};
