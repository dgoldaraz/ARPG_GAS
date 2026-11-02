// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroHUDWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "ARPGTags.h"
#include "HeroAttributeSet.h"
#include "UISettings.h"
#include "Components/AbilityInputComponent.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "ARPGTags.h"

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
		UpdateHealthBar();
		UpdateStaminaBar();
	}
	
	if (UAbilityInputComponent* AIC = InPawn->FindComponentByClass<UAbilityInputComponent>())
	{
		CacheAIC = AIC;
		// Listen to changes on input
		AIC->OnInputChangedDelegate.AddUObject(this, &ThisClass::OnInputChanged);
		UpdateInputs();
	}
}

void UHeroHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	/// Fill map 
	ImageMap.Add(GTags::InputActionUp, Image_Top);
	ImageMap.Add(GTags::InputActionLeft, Image_Left);
	ImageMap.Add(GTags::InputActionRight, Image_Right);
	ImageMap.Add(GTags::InputActionDown, Image_Bottom);
}

void UHeroHUDWidget::NativeDestruct()
{
	CleanListeners();
	Super::NativeDestruct();
}

void UHeroHUDWidget::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	// Update HealthBar
	UpdateHealthBar();
}

void UHeroHUDWidget::OnStaminaChanged(const FOnAttributeChangeData& ChangeData)
{
	// Update Stamina bar
	UpdateStaminaBar();
}

void UHeroHUDWidget::OnInputChanged(FGameplayTag inputTag, FGameplayTag actionTag)
{
	// Update input
	UpdateInputImage(inputTag, actionTag);
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

void UHeroHUDWidget::UpdateHealthBar()
{
	// Set bars based on ASC
	if (CacheASC.IsValid())
	{
		const float healthPercent = CacheASC.Get()->GetNumericAttribute(UHeroAttributeSet::GetHealthAttribute()) / CacheASC.Get()->GetNumericAttribute(UHeroAttributeSet::GetMaxHealthAttribute());
		Bar_Health->SetPercent(healthPercent);
	}
}

void UHeroHUDWidget::UpdateStaminaBar()
{
	if (CacheASC.IsValid())
	{
		const float staminaPercent = CacheASC.Get()->GetNumericAttribute(UHeroAttributeSet::GetStaminaAttribute()) / CacheASC.Get()->GetNumericAttribute(UHeroAttributeSet::GetMaxStaminaAttribute());
		Bar_Stamina->SetPercent(staminaPercent);
	}
}

void UHeroHUDWidget::UpdateInputs()
{
	// Set input images based on AIC
	if (UAbilityInputComponent* AIC = CacheAIC.Get())
	{
		UpdateInputImage(GTags::InputActionUp, AIC->GetTagByInput(GTags::InputActionUp));
		UpdateInputImage(GTags::InputActionLeft, AIC->GetTagByInput(GTags::InputActionLeft));
		UpdateInputImage(GTags::InputActionRight, AIC->GetTagByInput(GTags::InputActionRight));
		UpdateInputImage(GTags::InputActionDown, AIC->GetTagByInput(GTags::InputActionDown));
	}
}

void UHeroHUDWidget::UpdateInputImage(FGameplayTag inputTag, FGameplayTag abilityTag)
{
	if (abilityTag.IsValid())
	{
		ImageMap[inputTag]->SetVisibility(ESlateVisibility::HitTestInvisible);
		const UUISettings* UISettings = UUISettings::Get();
		if (const TSoftObjectPtr<UTexture2D>* iconPtr = UISettings->AbilityIcons.Find(abilityTag))
		{
			ImageMap[inputTag]->SetBrushFromSoftTexture(*iconPtr);
		}
	}
	else
	{
		ImageMap[inputTag]->SetVisibility(ESlateVisibility::Hidden);
	}
	
}
