// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	void Attach(UStaticMeshComponent* Parent, const FName& SocketName);
	void Detach();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
};
