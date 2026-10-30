// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "HeroHUDWidget.generated.h"


class UAbilitySystemComponent;
class UAbilityInputComponent;
class APawn;

/**
 * Main Hero HUD Widget showed on Player Character
 */
UCLASS()
class ARPG_GAS_API UHeroHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	// Initialize listeners
	void InitializeWithPawn(APawn* InPawn);
	
	virtual void NativeDestruct() override;
	
protected:
	
	void OnHealthChanged(const FOnAttributeChangeData& ChangeData);
	void OnStaminaChanged(const FOnAttributeChangeData& ChangeData);
	void OnInputChanged(FGameplayTag inputTag, FGameplayTag actionTag);
private:
	
	// Function to clean previously created listeners(if any)
	void CleanListeners();
	// Update vales directly that uses ASC
	void UpdateASCValues(UAbilitySystemComponent* AbilitySystemComponent);
	// Update Inputs based on AIC
	void UpdateInputs(UAbilityInputComponent* inputComponent);
	
private:
	
	// Cache components
	TWeakObjectPtr<UAbilitySystemComponent> CacheASC;
	TWeakObjectPtr<UAbilityInputComponent> CacheAIC;
};
