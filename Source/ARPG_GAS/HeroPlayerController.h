// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPG_GASPlayerController.h"
#include "HeroPlayerController.generated.h"

class UHeroHUDWidget;


/**
 * Hero Player Controller class
 */
UCLASS()
class ARPG_GAS_API AHeroPlayerController : public AARPG_GASPlayerController
{
	GENERATED_BODY()
	
public:
	// 
	virtual void BeginPlay() override;
protected:
	UFUNCTION()
	void HandlePawnChanged(APawn* oldPawn, APawn* newPawn);
private:

	// Method to initialize HUD Widget
	void InitializeHUDWidget(APawn* newPawn);
	
protected:
	// Hud Class
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHeroHUDWidget> HUDWidgetClass;
	
	// Hud Widget
	UPROPERTY(Transient)
	TObjectPtr<UHeroHUDWidget> HUDWidget;
};
