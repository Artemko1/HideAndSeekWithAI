// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGCoreTypes.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "DGMoveToWithSpeedModeBTTaskNode.generated.h"


UCLASS()
class HIDEANDSEEKWITHAI_API UDGMoveToWithSpeedModeBTTaskNode : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UDGMoveToWithSpeedModeBTTaskNode();
	
	UPROPERTY(Category = Node, EditAnywhere)
	EDGMovementSpeedMode DGMovementSpeedMode = EDGMovementSpeedMode::Default;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
};
