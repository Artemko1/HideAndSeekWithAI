// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DGFindEnemyBTService.h"

#include "AIController.h"
#include "AI/DGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Класс НЕ используется, почему - написано в .h файле
UDGFindEnemyBTService::UDGFindEnemyBTService()
{
	NodeName = "DEPRECATEDFind Enemy";
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

	const auto PerceptionComponent = Cast<UDGAIPerceptionComponent>(AIController->GetAIPerceptionComponent());
	if (!PerceptionComponent)
	{
		return;
	}

	TArray<AActor*> HostileActors;
	PerceptionComponent->GetHostileActors(HostileActors);

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
		
		// По итогу всё же перенёс логику
		
		Blackboard->SetValueAsVector(EnemyLastSeenLocationKey.SelectedKeyName, Enemy->GetActorLocation());
	}
}
