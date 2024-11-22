// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreZone.h"

AScoreZone::AScoreZone() {
	OnActorEndOverlap.AddDynamic(this, &AScoreZone::ActorOverlap);
}

void AScoreZone::BeginPlay() {
	Super::BeginPlay();
}

void AScoreZone::ActorOverlap(class AActor* Self, class AActor* OtherActor) {
	if (OtherActor && OtherActor != this) {
		ASkaterCharacter* Character = Cast<ASkaterCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (OtherActor == Character) {
			ASkateGameState* GameState = Cast<ASkateGameState>(GetWorld()->GetGameState());
			GameState->Score += ScoreAmount;
		}
	}
}