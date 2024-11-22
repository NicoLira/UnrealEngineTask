// Fill out your copyright notice in the Description page of Project Settings.


#include "SkaterController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SkaterCharacter.h"

void ASkaterController::BeginPlay() {
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	if (WidgetTemplate) {
		if (!WidgetInstance) {
			WidgetInstance = CreateWidget(this, WidgetTemplate);
		}
		if (!WidgetInstance->GetIsVisible()) {
			WidgetInstance->AddToViewport();
		}
	}

	SetupPlayerInputController();
}

void ASkaterController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	
}

void ASkaterController::SetupPlayerInputController() {
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkaterController::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASkaterController::Move);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASkaterController::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASkaterController::JumpCompleted);
	}
}

void ASkaterController::Move(const FInputActionInstance& Instance) {
	FVector2D InputVector = Instance.GetValue().Get<FVector2D>();
	if (ASkaterCharacter* SkaterPawn = Super::GetPawn<ASkaterCharacter>()) {
		SkaterPawn->Move(InputVector);
	}
}

void ASkaterController::JumpStarted() {
	if (ASkaterCharacter* SkaterPawn = Super::GetPawn<ASkaterCharacter>()) {
		SkaterPawn->JumpCharge();
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("JumpStarted!"));	
	}
}

void ASkaterController::JumpCompleted() {
	if (ASkaterCharacter* SkaterPawn = Super::GetPawn<ASkaterCharacter>()) {
		SkaterPawn->JumpRelease();
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("JumpCompleted!"));	
	}
}