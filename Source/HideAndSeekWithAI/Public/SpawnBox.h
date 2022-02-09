// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBox.generated.h"

class UBoxComponent;
UCLASS()
class HIDEANDSEEKWITHAI_API ASpawnBox : public AActor
{
	GENERATED_BODY()

public:
	ASpawnBox();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UBoxComponent* AreaBox;

	virtual void BeginPlay() override;

	// Must be called before GetNextRandomPoint2D()
	UFUNCTION(BlueprintCallable)
	void InitializeBounds();

	UFUNCTION(BlueprintCallable)
	FVector2D GetNextRandomPoint2D(int Index);

private:
	/// 0-1 range
	FVector2D PrevValue;
	/// 0-1 range
	FVector2D XBoxLocationVector;
	/// 0-1 range
	FVector2D YBoxLocationVector;

	bool IsInitialized = false;
};
