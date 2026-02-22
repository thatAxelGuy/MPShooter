// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlasterPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/BlasterCharacter.h"
#include "GameFramework/Character.h"


ABlasterPlayerController::ABlasterPlayerController()
{
	bReplicates = true;
}

void ABlasterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(BlasterContext);
	
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(BlasterContext, 0);
	
}

void ABlasterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ABlasterPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABlasterPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABlasterPlayerController::JumpStarted);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABlasterPlayerController::JumpCompleted);
}

void ABlasterPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ABlasterPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	AddPitchInput(LookAxisVector.Y);
	AddYawInput(LookAxisVector.X);
	
}

void ABlasterPlayerController::JumpStarted()
{
	if (ACharacter* Char = Cast<ABlasterCharacter>(GetPawn()))
	{
		Char->Jump();
	}
}

void ABlasterPlayerController::JumpCompleted()
{
	if (ACharacter* Char = Cast<ABlasterCharacter>(GetPawn()))
	{
		Char->StopJumping();
	}
}





