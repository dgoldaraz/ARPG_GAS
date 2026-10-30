// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HeroAttributeSet.generated.h"

/**
 * Hero Attribute Set
 */

// Macro to easily declare attributes by : https://www.youtube.com/watch?v=NCCs4hxU6fY
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
 
// Data Table definiton for Hero Attributes
USTRUCT(Blueprintable)
struct FHeroAttributeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	
	FHeroAttributeData() : Health(100.0f), MaxHealth(100.0f)
	{
	};
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Health = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Stamina = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float MaxStamina = 100.0f;
};

UCLASS()
class ARPG_GAS_API UHeroAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHeroAttributeSet();
	
	// Override UAttributeSet
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
	// Current Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_CurrentHealth)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, Health)
	
	// Max Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MaxHealth)
	
	// Current Stamina
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_CurrentStamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, Stamina)
	
	// Max Stamina
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MaxStamina)

protected:
	
	// Updates whenever a character Health changes. Will ensure that current health it's updated and synched
	// Clients updates when attribute changes
	UFUNCTION()
	virtual void OnRep_CurrentHealth(const FGameplayAttributeData &OldCurrentHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_CurrentStamina(const FGameplayAttributeData &OldCurrentStamina);
	
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData &OldMaxStamina);
	
	// Marks the properties we want to replicate
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
