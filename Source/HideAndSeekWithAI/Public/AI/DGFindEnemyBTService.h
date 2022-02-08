// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DGFindEnemyBTService.generated.h"


/* Этот класс НЕ используется. Я оставил этот файл только чтобы побольше показать как я делал задание.
 * Логика этого сервиса перенесена в блупринт DGAIController и подвязана на ивенты восприятия, чтобы бот реагировал мгновенно, а не тиками.
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UDGFindEnemyBTService : public UBTService
{
	GENERATED_BODY()

public:
	UDGFindEnemyBTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyLastSeenLocationKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
