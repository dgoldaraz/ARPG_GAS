// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroPlayerController.h"

#include "AbilitySystemInterface.h"
#include "HeroHUDWidget.h"

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Early escape if no HUD Class or not on client
	if (!IsLocalController() || !IsValid(HUDWidgetClass))
	{
		return;
	}
	
	HUDWidget = CreateWidget<UHeroHUDWidget>(this, HUDWidgetClass);
	
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
	
	OnPossessedPawnChanged.AddDynamic(this,&ThisClass::HandlePawnChanged);
	
	InitializeHUDWidget(GetPawn());
}

void AHeroPlayerController::HandlePawnChanged(APawn* oldPawn, APawn* newPawn)
{
	if (!IsLocalController() || !HUDWidget)
	{
		return;
	}

	// Initialize HUD
	InitializeHUDWidget(newPawn);
}

void AHeroPlayerController::InitializeHUDWidget( APawn* newPawn)
{
	if (!IsValid(newPawn))
	{
		return;
	}
	
	// Initialize HUD
	if (IsLocalController())
	{
		if (!IsValid(HUDWidget))
		{
			return;
		}
		
		HUDWidget->InitializeWithPawn(newPawn);
	}
}
