// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityInputComponent.h"
#include "ARPGTags.h"
#include "EnhancedInputComponent.h"
#include "HeroCharacter.h"


// Sets default values for this component's properties
UAbilityInputComponent::UAbilityInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

void UAbilityInputComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Actions bindings
		for (const auto& inputBinding : AbilityInputBindings)
		{
			EnhancedInputComponent->BindAction(inputBinding.InputAction, ETriggerEvent::Started, this, &ThisClass::OnActionPressed, inputBinding.InputTag);
		}
	}
}

void UAbilityInputComponent::RegisterAbility(const TSubclassOf<UGameplayAbility> ability, FGameplayTag inputTag)
{
	if (!inputTag.IsValid())
	{
		return;
	}
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}
	
	//Save ability on the map
	
	FAbilityInfo newInfo;
	newInfo.AbilityClass = ability;
	
	if (FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(ability))
	{
		newInfo.AbilityHandle = Spec->Handle;
	}
	FGameplayTagContainer abilityTags = ability.GetDefaultObject()->GetAssetTags();
	// ensure we only have one tag
	ensure(abilityTags.Num() == 1);
	newInfo.AbilityTag = abilityTags.GetByIndex(0);
	
	if (auto oldAbility = abilitySlot.Find(inputTag))
	{
		if (oldAbility->AbilityClass == ability)
		{
			return;
		}
		abilitySlot[inputTag] = newInfo;
	}
	else
	{
		abilitySlot.Add(inputTag, newInfo);
	}
	
	OnInputChangedDelegate.Broadcast(inputTag, newInfo.AbilityTag);
}

FGameplayTag UAbilityInputComponent::GetTagByInput(FGameplayTag inputTag) const
{
	FGameplayTag result;
	if (inputTag.IsValid() && abilitySlot.Contains(inputTag))
	{
		result = abilitySlot[inputTag].AbilityTag;
	}
	return result;
}

void UAbilityInputComponent::OnActionPressed(FGameplayTag actionTag)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}
	
	if (FAbilityInfo* info = abilitySlot.Find(actionTag))
	{
		if (!info->AbilityHandle.IsValid())
		{
			//Search for the handle in case is not set
			if (FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(info->AbilityClass))
			{
				info->AbilityHandle = Spec->Handle;
			}
		}
		
		if (info->AbilityHandle.IsValid())
		{
			ASC->TryActivateAbility(info->AbilityHandle);
		}
		// TODO: Add info if ability is not found
	}
}

UAbilitySystemComponent* UAbilityInputComponent::GetAbilitySystemComponent() const
{
	if (const AHeroCharacter* ownerCharacter = Cast<AHeroCharacter>(GetOwner()))
	{
		return ownerCharacter->GetAbilitySystemComponent();
	}
	return nullptr;
}

