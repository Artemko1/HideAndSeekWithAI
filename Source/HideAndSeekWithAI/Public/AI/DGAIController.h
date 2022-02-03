// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "DGAIController.generated.h"

class UDGAIPerceptionComponent;
UCLASS()
class HIDEANDSEEKWITHAI_API ADGAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADGAIController();

protected:
	virtual void BeginPlay() override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UDGAIPerceptionComponent* DGAIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName SpawnBBKeyName;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamId;
};
