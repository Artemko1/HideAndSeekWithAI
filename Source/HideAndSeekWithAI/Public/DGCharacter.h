// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Item.h"
#include "DGCharacter.generated.h"

class UCameraComponent;

// IGenericTeamAgentInterface имплементился, потому что сначала хотел сделать видимость игроков на нём (чтобы других ботов не видел).
// Но поскольку по итогу сделал поиск игрока через Cast к DGPlayerCharacter, то система команд в принципе стала не нужна больше.
// Оставил, чтобы показать процесс решения ТЗ.
UCLASS()
class HIDEANDSEEKWITHAI_API ADGCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	explicit ADGCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FName ItemSocketName = "ItemSocket";


	virtual void BeginPlay() override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override { TeamId = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	void PickupItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void DropItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ThrowItem(float Force);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool IsHoldingItem() const { return HeldItem != nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool GetItemSpawnLocation(FVector& OutLocation) const;

	void SetMaxSpeed(float Speed) const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetBaseSpeed() const { return BaseSpeed; }

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamId = FGenericTeamId::NoTeam;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	AItem* HeldItem;

	float BaseSpeed = 500.f;
};
