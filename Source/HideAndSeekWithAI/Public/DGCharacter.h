// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "DGCharacter.generated.h"

class UCameraComponent;
UCLASS()
class HIDEANDSEEKWITHAI_API ADGCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	explicit ADGCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{
		TeamId = TeamID;
	}

	virtual FGenericTeamId GetGenericTeamId() const override
	{
		return TeamId;
	}

	void SetMaxSpeed() const;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamId = FGenericTeamId::NoTeam;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float BaseSpeedMultiplier = 1.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Item")
	USceneComponent* HeldItemLocation;

	float BaseSpeed = 500.f;
};
