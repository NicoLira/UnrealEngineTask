// Fill out your copyright notice in the Description page of Project Settings.


#include "SkaterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASkaterCharacter::ASkaterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkaterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();

	if (!MovementComp->IsFalling()) {
		FVector GroundVel = MovementComp->Velocity;
		GroundVel.Z = 0.0;
		float DotGroundVelDir = GroundVel.GetSafeNormal().Dot(GetActorForwardVector());
		
		FVector ResultVel = (GetActorForwardVector() * DotGroundVelDir) * GroundVel.Length();
		ResultVel.Z = MovementComp->Velocity.Z;

		MovementComp->Velocity = ResultVel;

		if (ChargingJump) {
			MovementComp->JumpZVelocity = FMath::Clamp(MovementComp->JumpZVelocity + (DeltaTime * 300.0), 0.0, 700.0);
		}
	}
}

// Called to bind functionality to input
void ASkaterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASkaterCharacter::Move(FVector2D InputVector) {
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	float AirBonus = (float)MovementComp->IsFalling() * OnAirRotationSpeedBonus;
	AddControllerYawInput((AirBonus + BaseRotationSpeed) * InputVector.X);

	if (!MovementComp->IsFalling()) {
		if (InputVector.Y >= 0.0) {
			AddMovementInput(GetActorForwardVector(), FMath::Clamp(InputVector.Y, 0.0, 1.0));
			if (InputVector.Y > 0.0) {
				Pushing = true;
			}
			else {
				Pushing = false;
			}
		}
		else {
			GetMovementComponent()->Velocity *= 0.85;
			Pushing = false;
		}
	}
}

void ASkaterCharacter::JumpCharge() {
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
 	ChargingJump = true;
	MovementComp->JumpZVelocity = 400.0;
}

void ASkaterCharacter::JumpRelease() {
	Jump();
	ChargingJump = false;
}