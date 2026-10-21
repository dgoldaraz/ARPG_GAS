// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ARPG_GASCharacter.h"
#include "HeroAttributeSet.h"
#include "HeroCharacter.generated.h"

UCLASS()
class ARPG_GAS_API AHeroCharacter : public AARPG_GASCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	// Implement the interface method to return an AbilitySystemComponent
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Called when this player is possessed in server
	virtual void PossessedBy(AController* NewController) override;
	// Called when client has info of the controller
	virtual void OnRep_Controller() override;
	
protected:
	void InitializeAbilityActorInfo();
	void InitializeGAS();

private:
	// If a GE is set, try to use it to initialize attributes
	void InitializeUsingGE(FHeroAttributeData* Data) const;
	
	// Uses direct access to attributes for configuration
	void InitializeByCall(FHeroAttributeData* Data) const;
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// ASC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;
	
	// Hero Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	UHeroAttributeSet* HeroAttributeSet;
	
	// Data storing different archetypes to initialize attributes
	UPROPERTY(EditAnywhere, Category = "Attributes")
	FDataTableRowHandle HeroAttributeData;
	
	// Initial GE to initialize attributes
	UPROPERTY(EditAnywhere, Category = "GAS|Initialization")
	TSubclassOf<UGameplayEffect> InitialAttributesEffect;
	
	// Initialize attributes (Can be called on Initialization)
	void InitializeAttributes() const;
	
	// Initialize Abilities 
	void InitializeAbilities();
	
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> HeroInitialAbilities;
};
