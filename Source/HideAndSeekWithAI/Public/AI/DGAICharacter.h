// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGCharacter.h"
#include "DGAICharacter.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API ADGAICharacter : public ADGCharacter
{
	GENERATED_BODY()

public:
	explicit ADGAICharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
};
