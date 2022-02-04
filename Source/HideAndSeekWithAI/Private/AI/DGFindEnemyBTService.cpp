// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DGFindEnemyBTService.h"

#include "AIController.h"
#include "AI/DGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


UDGFindEnemyBTService::UDGFindEnemyBTService()
{
	NodeName = "Find Enemy";
}

void UDGFindEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto AIController = OwnerComp.GetAIOwner();
	if (!Blackboard || !AIController)
	{
		return;
	}

	const auto Pawn = AIController->GetPawn();
	const auto PerceptionComponent = Cast<UDGAIPerceptionComponent>(AIController->GetAIPerceptionComponent());
	if (!PerceptionComponent || !Pawn)
	{
		return;
	}

	TArray<AActor*> HostileActors;
	PerceptionComponent->GetHostileActors(HostileActors);

	//todo remove debug code
	for (const auto HostileActor : HostileActors)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Cyan,
										 FString::Printf(TEXT("%s sees %s"), *Pawn->GetName(), *HostileActor->GetName()));
		}
	}

	AActor* Enemy = nullptr;
	if (HostileActors.Num() >= 1)
	{
		Enemy = HostileActors[0];
	}

	Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Enemy);
	if (Enemy)
	{
		// Возможно последнюю позицию можно доставать из ивента OnTargetPerceptionUpdated, а не перезаписывать в Тике,
		// но я решил сделать способом попроще.
		Blackboard->SetValueAsVector(EnemyLastSeenLocationKey.SelectedKeyName, Enemy->GetActorLocation());
	}
}
