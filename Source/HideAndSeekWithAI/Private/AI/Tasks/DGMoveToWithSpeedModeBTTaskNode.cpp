// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/DGMoveToWithSpeedModeBTTaskNode.h"

#include "AIController.h"
#include "AI/DGAICharacter.h"

UDGMoveToWithSpeedModeBTTaskNode::UDGMoveToWithSpeedModeBTTaskNode()
{
	NodeName = "Move To With Speed Mode";
}

EBTNodeResult::Type UDGMoveToWithSpeedModeBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (MyController)
	{
		ADGAICharacter* DGAICharacter = MyController->GetPawn<ADGAICharacter>();
		if (DGAICharacter)
		{
			DGAICharacter->SetMovementMode(DGMovementSpeedMode);
		}
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UDGMoveToWithSpeedModeBTTaskNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (MyController)
	{
		ADGAICharacter* DGAICharacter = MyController->GetPawn<ADGAICharacter>();
		if (DGAICharacter)
		{
			DGAICharacter->SetMovementMode(EDGMovementSpeedMode::Default);
		}
	}

	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
