// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABlasterPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* MovementAction;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* JumpAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void JumpStarted();
	void JumpCompleted();
	
private:
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputMappingContext> BlasterContext;
};
