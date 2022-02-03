// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "DGAIPerceptionComponent.generated.h"


UCLASS()
class HIDEANDSEEKWITHAI_API UDGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	// Тут был функционал, который я решил перенести в сервис. Класс оставил, потому что он создан в персонаже бота, чтобы настройки не слетели
	// И в целом считаю, что такие прослойки делать полезно на случай, если понадобится дополнительный функционал во всех наследниках.
};
