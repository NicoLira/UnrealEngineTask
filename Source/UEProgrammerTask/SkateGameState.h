// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SkateGameState.generated.h"

/**
 * 
 */
UCLASS()
class UEPROGRAMMERTASK_API ASkateGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	int Score = 0;

};
