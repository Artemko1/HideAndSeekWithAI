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

	// Пытался использовать NodeMemory, но видимо из-за размера в uint8 память не смогла поместить в себя 4 параметра и поэтому
	// периодически крашила игру при запуске (при чём не смотря на null-check!).
	// Так же инстанс-меш поля зрения почему-то не обновлялся при повороте персонажа без этой настройки, что интересно.
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UDGTurnBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TargetTurnSpeed = FMath::FRandRange(FMath::Max(0.0f, TurnSpeed - TurnSpeedDeviation), (TurnSpeed + TurnSpeedDeviation));
	TargetTurnAngle = FMath::FRandRange(FMath::Max(0.0f, TurnAngle - TurnAngleDeviation), (TurnAngle + TurnAngleDeviation));
	TargetDirectionIsRight = IsRandomDirection ? FMath::RandBool() : IsRotatingRight;
	ElapsedTurn = 0;

	return EBTNodeResult::InProgress;
}

void UDGTurnBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	FRotator Rotation = AIController->GetControlRotation();
	const float Delta = DeltaSeconds * TargetTurnSpeed;

	TargetDirectionIsRight ? Rotation.Yaw += Delta : Rotation.Yaw -= Delta;
	ElapsedTurn += Delta;

	Pawn->SetActorRotation(Rotation);

	if (ElapsedTurn >= TargetTurnAngle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}
