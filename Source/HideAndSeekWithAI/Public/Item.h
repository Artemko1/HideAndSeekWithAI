// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	UFUNCTION(BlueprintCallable)
	FVector GetSpawnLocation() const { return SpawnLocation; }

	UFUNCTION(BlueprintCallable)
	bool IsOnSpawn() const { return bIsOnSpawn; }

	void Attach(UStaticMeshComponent* Parent, const FName& SocketName);
	void Detach();
	void AddImpulse(float Force) const;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadWrite)
	FVector SpawnLocation;

	bool bIsOnSpawn;

	virtual void BeginPlay() override;
};
