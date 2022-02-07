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

	bool Attach(UStaticMeshComponent* Parent, const FName& SocketName);
	bool Detach(AController* InstigatorController);
	void AddImpulse(float Force) const;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadWrite)
	FVector SpawnLocation;

	// Я хотел сделать дополнительную проверку, чтобы боты не брали кубы, которые меньше чем в метре от своего спауна.
	// Без неё боты в теории могут взять не тот куб, если несколько кубов скидать вместе.
	// Но решил, что вовершенствовать задание бесконечно можно, но и без этой фичи будет норм.
	// bool bIsOnSpawn;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	bool IsDroppedByPlayer() const { return bIsDroppedByPlayer; }

private:
	// Нужна проверка для того, чтобы нельзя было выхватить предмет из рук у бота.
	bool IsAttached = false;

	bool bIsDroppedByPlayer = false;
};
