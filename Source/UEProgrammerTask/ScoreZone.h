// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SkaterCharacter.h"
#include "SkateGameState.h"
#include "ScoreZone.generated.h"

/**
 * 
 */
UCLASS()
class UEPROGRAMMERTASK_API AScoreZone : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	AScoreZone();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void ActorOverlap(class AActor* Self, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	int ScoreAmount = 300;
};
