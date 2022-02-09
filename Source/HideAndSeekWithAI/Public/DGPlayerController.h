// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()
	// Подобные классы создаю заранее, потому что сначала неизвестно, понадобятся ли, а потом будет дольше везде заменять
};
