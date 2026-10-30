// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroHUDWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "HeroAttributeSet.h"
#include "Components/AbilityInputComponent.h"

void UHeroHUDWidget::InitializeWithPawn(APawn* InPawn)
{
	if (!IsValid(InPawn))
	{
		return;
	}
	
	
	
	IAbilitySystemInterface* ASI =Cast<IAbilitySystemInterface>(InPawn);
	if (!ASI)
	{
		return;
	}
	
	CleanListeners();
	
	if (UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent())
	{
		CacheASC = ASC;
		// Listen to changes on attributes
		ASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetStaminaAttribute()).AddUObject(this, &ThisClass::OnStaminaChanged);
		UpdateASCValues(ASC);
	}
	
	if (UAbilityInputComponent* AIC = InPawn->FindComponentByClass<UAbilityInputComponent>())
	{
		CacheAIC = AIC;
		// Listen to changes on input
		AIC->OnInputChangedDelegate.AddUObject(this, &ThisClass::OnInputChanged);
		UpdateInputs(AIC);
	}
}

void UHeroHUDWidget::NativeDestruct()
{
	CleanListeners();
	Super::NativeDestruct();
}

void UHeroHUDWidget::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	// Update HealthBar
}

void UHeroHUDWidget::OnStaminaChanged(const FOnAttributeChangeData& ChangeData)
{
	// Update Stamina bar
}

void UHeroHUDWidget::OnInputChanged(FGameplayTag inputTag, FGameplayTag actionTag)
{
	// Update input
}


void UHeroHUDWidget::CleanListeners()
{
	// Remove previous Delegates
	if (CacheASC.IsValid())
	{
		if (UAbilitySystemComponent* oldASC = CacheASC.Get())
		{
			oldASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetHealthAttribute()).RemoveAll(this);
			oldASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetStaminaAttribute()).RemoveAll(this);
		}
	}
	
	if (CacheAIC.IsValid())
	{
		if (UAbilityInputComponent* oldAIC = CacheAIC.Get())
		{
			oldAIC->OnInputChangedDelegate.RemoveAll(this);
		}
	}
}

void UHeroHUDWidget::UpdateASCValues(UAbilitySystemComponent* AbilitySystemComponent)
{
	// Set bars based on ASC
}

void UHeroHUDWidget::UpdateInputs(UAbilityInputComponent* inputComponent)
{
	// Set input images based on AIC
}
