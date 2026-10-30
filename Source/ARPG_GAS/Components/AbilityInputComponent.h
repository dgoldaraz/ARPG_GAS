// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "AbilityInputComponent.generated.h"

class UInputComponent;
class UInputAction;
class UGameplayAbility;
class UAbilitySystemComponent;

// Declare delegate when input change action
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInputChanged, FGameplayTag inputTag, FGameplayTag actionTag );

USTRUCT(BlueprintType)
struct FAbilityInputBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
};

USTRUCT()
struct FAbilityInfo
{
	GENERATED_BODY()
	
	// Class used
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	//Handle 
	FGameplayAbilitySpecHandle AbilityHandle;
	
	// Ability Tag
	FGameplayTag AbilityTag;
};

/*
 * Component to manage binding between Enhanced Input and abilities.
 * Will be responsible to know which input is associated wich wich ability and 
 * tries to activate it
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARPG_GAS_API UAbilityInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityInputComponent();
	
	// Setup input
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	
	// Register an ability on a specific tag
	void RegisterAbility(const TSubclassOf<UGameplayAbility> ability, FGameplayTag inputTag);
	
	// Return ability tag associated for input if any
	FGameplayTag GetTagByInput(FGameplayTag inputTag) const;

protected:
	// Function for Action1 press
	UFUNCTION(BlueprintCallable)
	void OnActionPressed(FGameplayTag actionTag);
	
public:
	// Delegate called when input changes
	FOnInputChanged OnInputChangedDelegate;
	
private:
	// Implement the interface method to return an AbilitySystemComponent
	UAbilitySystemComponent* GetAbilitySystemComponent() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<FAbilityInputBinding> AbilityInputBindings;
	
private:
	
	// Cache tag <-> ability info
	UPROPERTY(Transient)
	TMap<FGameplayTag, FAbilityInfo> abilitySlot;
};
