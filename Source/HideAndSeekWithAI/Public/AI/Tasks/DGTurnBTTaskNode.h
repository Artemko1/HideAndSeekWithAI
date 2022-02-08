// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGTurnBTTaskNode.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API UDGTurnBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDGTurnBTTaskNode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	/** in degrees per second */
	UPROPERTY(Category = LookAround, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "360.0", UIMax = "360.0"))
	float TurnSpeed = 30.f;

	UPROPERTY(Category = LookAround, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
	float TurnSpeedDeviation = 0.f;

	/** in degrees */
	UPROPERTY(Category = LookAround, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "360.0", UIMax = "360.0"))
	float TurnAngle = 90.f;

	UPROPERTY(Category = LookAround, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
	float TurnAngleDeviation = 0.f;

	UPROPERTY(Category = LookAround, EditAnywhere)
	bool IsRandomDirection = true;

	UPROPERTY(Category = LookAround, EditAnywhere, meta = (EditCondition = "!IsRandomDirection"))
	bool IsRotatingRight = true;


	float TargetTurnSpeed = 0;
	float TargetTurnAngle = 0;
	bool TargetDirectionIsRight = true;

	/** How much from TargetTurnAngle Pawn already turned */
	float ElapsedTurn = 0;
};
