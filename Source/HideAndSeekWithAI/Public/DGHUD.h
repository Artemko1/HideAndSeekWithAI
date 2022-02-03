// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DGHUD.generated.h"

/// Simple implementation taken from 1st person template
UCLASS()
class HIDEANDSEEKWITHAI_API ADGHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="HUD")
	UTexture2D* CrosshairTex;
};
