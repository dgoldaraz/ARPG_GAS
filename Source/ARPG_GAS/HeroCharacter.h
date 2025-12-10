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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	
	// ASC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;
	
	// Hero Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	UHeroAttributeSet* HeroAttributeSet;
	
	UPROPERTY(EditAnywhere, Category = "Attributes")
	FDataTableRowHandle HeroAttributeData;
	
	// Initialize attributes (Can eb called on Initialization)
	void InitializeAttributes();
};
