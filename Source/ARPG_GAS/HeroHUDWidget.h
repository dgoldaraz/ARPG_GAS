// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "HeroHUDWidget.generated.h"


class UAbilitySystemComponent;
class UAbilityInputComponent;
class UProgressBar;
class UImage;

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
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
protected:
	
	void OnHealthChanged(const FOnAttributeChangeData& ChangeData);
	void OnStaminaChanged(const FOnAttributeChangeData& ChangeData);
	void OnInputChanged(FGameplayTag inputTag, FGameplayTag actionTag);
private:
	
	// Function to clean previously created listeners(if any)
	void CleanListeners();
	// Update HealthBar
	void UpdateHealthBar();
	// Update StaminaBar
	void UpdateStaminaBar();
	// Update Inputs based on AIC
	void UpdateInputs();
	// Update Input image
	void UpdateInputImage(FGameplayTag inputTag, FGameplayTag abilityTag);
	
protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag TopActionTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag LeftActionTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag RightActionTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag BottomActionTag;
	
	// Bars
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_Health;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar_Stamina;
	
	// Input Images
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Image_Top;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Image_Left;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Image_Right;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Image_Bottom;
private:
	
	// Cache components
	TWeakObjectPtr<UAbilitySystemComponent> CacheASC;
	TWeakObjectPtr<UAbilityInputComponent> CacheAIC;
	
	// Map for accessing images by tag
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UImage>> ImageMap;
};
