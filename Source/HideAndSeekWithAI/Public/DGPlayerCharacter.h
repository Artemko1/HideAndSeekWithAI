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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0, UIMin = 0))
	float ItemPickupRange = 350.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0, UIMin = 0))
	float ItemMinThrowForce = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0, UIMin = 0))
	float ItemMaxThrowForce = 3000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0, UIMin = 0))
	float ItemThrowMaxChargeTime = 2.f;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	FTimerHandle ChargeThrowTimerHandle;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void ChargeThrow();
	void ReleaseThrow();

	void TryPickupItem();
};
