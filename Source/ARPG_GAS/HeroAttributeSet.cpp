// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UHeroAttributeSet::UHeroAttributeSet()
	: Health(100.0f), MaxHealth(100.0f)
{
}

void UHeroAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	//Called just after a GameplayEffect is executed to modify the base value of an attribute
	Super::PostGameplayEffectExecute(Data);
	
	static FProperty* HealthProperty = FindFieldChecked<FProperty>(UHeroAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UHeroAttributeSet, Health));
	//static FProperty* DamageProperty = FindFieldChecked<FProperty>(UHeroAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UAbilitySystemTestAttributeSet, Damage));

	FProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();

	// What property was modified?
	// DO calculations based on this
	//if (DamageProperty == ModifiedProperty)
	//{
}

void UHeroAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, Health, OldCurrentHealth);
}

void UHeroAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, MaxHealth, OldMaxHealth);
}

void UHeroAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, Stamina, OldCurrentStamina);
}

void UHeroAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, MaxStamina, OldMaxStamina);
}

void UHeroAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	/*
	Unreal Engine actors maintain a list of all properties with the Replicated and ReplicatedUsing metadata specifiers.
	When a property is marked with a Replicated or ReplicatedUsing metadata specifier during multiplayer gameplay,
	the server sends an update to each connected client whenever a replicated property changes its value.
	Each client applies the updated value to its local version of the actor.
	https://dev.epicgames.com/documentation/en-us/unreal-engine/replicate-actor-properties-in-unreal-engine
	*/
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Define what needs to be replicated with clients
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}
