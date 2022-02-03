// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DGAIController.h"

#include "DGCoreTypes.h"
#include "AI/DGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogDGAIController, All, All)

ADGAIController::ADGAIController()
{
	DGAIPerceptionComponent = CreateDefaultSubobject<UDGAIPerceptionComponent>("DGAIPerceptionComponent");
	SetPerceptionComponent(*DGAIPerceptionComponent);

	AAIController::SetGenericTeamId(FGenericTeamId(static_cast<uint8>(EDGTeams::Bots)));
}

void ADGAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BTAsset);

	if (GetBlackboardComponent() && GetPawn())
	{
		if (SpawnBBKeyName.IsNone())
		{
			UE_LOG(LogDGAIController, Warning, TEXT("SpawnBBKeyName is set to None"));
		}

		GetBlackboardComponent()->SetValueAsVector(SpawnBBKeyName, GetPawn()->GetActorLocation());
	}
}

ETeamAttitude::Type ADGAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		FGenericTeamId TeamA = GetGenericTeamId();
		FGenericTeamId TeamB = OtherTeamAgent->GetGenericTeamId();
		ETeamAttitude::Type Attitude = FGenericTeamId::GetAttitude(TeamA, TeamB);
		return Attitude;
	}

	return ETeamAttitude::Neutral;
}
