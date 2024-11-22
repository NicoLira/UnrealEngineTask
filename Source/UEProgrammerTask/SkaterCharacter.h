// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkaterCharacter.generated.h"

UCLASS()
class UEPROGRAMMERTASK_API ASkaterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkaterCharacter();

	void Move(FVector2D InputVector);
	
	void JumpCharge();
	void JumpRelease();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float BaseRotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float OnAirRotationSpeedBonus;

	UPROPERTY(BlueprintReadOnly)
	bool ChargingJump;

	UPROPERTY(BlueprintReadOnly)
	bool Pushing;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
