// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGCharacter.h"
#include "DGPlayerCharacter.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API ADGPlayerCharacter : public ADGCharacter
{
	GENERATED_BODY()
public:
	explicit ADGPlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
};
