// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverHeadWidget.h"

#include "Components/TextBlock.h"


void UOverHeadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverHeadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;
	switch (LocalRole)
	{
		case ENetRole::ROLE_Authority:
			Role = FString("Authority");
			break;
		case ENetRole::ROLE_AutonomousProxy:
			Role = FString("AutonomousProxy");
			break;
		case ENetRole::ROLE_SimulatedProxy:
			Role = FString("SimulatedProxy");
			break;
		case ROLE_None:
			Role = FString("None");
			break;
		default: ;
	}
	
	FString LocalRoleString = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(LocalRoleString);
}

void UOverHeadWidget::NativeConstruct()
{
	RemoveFromParent();
	Super::NativeConstruct();
	
}
