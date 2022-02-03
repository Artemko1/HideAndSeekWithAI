// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DGTurnBTTaskNode.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UDGTurnBTTaskNode::UDGTurnBTTaskNode()
{
	NodeName = "LookAround";
	bNotifyTick = true;
	TurnSpeed = 30.f;
	TurnAngle = 90.f;
	TurnSpeedDeviation = 0.f;
	TurnAngleDeviation = 0.f;
}

EBTNodeResult::Type UDGTurnBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FDGTurnBTTaskMemory* MyMemory = (FDGTurnBTTaskMemory*)NodeMemory;

	MyMemory->TargetTurnSpeed = FMath::FRandRange(FMath::Max(0.0f, TurnSpeed - TurnSpeedDeviation), (TurnSpeed + TurnSpeedDeviation));
	MyMemory->TargetTurnAngle = FMath::FRandRange(FMath::Max(0.0f, TurnAngle - TurnAngleDeviation), (TurnAngle + TurnAngleDeviation));
	MyMemory->ElapsedTurn = 0;
	MyMemory->TargetDirectionIsRight = IsRandomDirection ? FMath::RandBool() : IsRotatingRight;

	return EBTNodeResult::InProgress;
}

void UDGTurnBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	FDGTurnBTTaskMemory* MyMemory = (FDGTurnBTTaskMemory*)NodeMemory;

	FRotator Rotation = AIController->GetControlRotation();
	const float Delta = DeltaSeconds * MyMemory->TargetTurnSpeed;

	MyMemory->TargetDirectionIsRight ? Rotation.Yaw += Delta : Rotation.Yaw -= Delta;
	MyMemory->ElapsedTurn += Delta;

	Pawn->SetActorRotation(Rotation);

	if (MyMemory->ElapsedTurn >= MyMemory->TargetTurnAngle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}
