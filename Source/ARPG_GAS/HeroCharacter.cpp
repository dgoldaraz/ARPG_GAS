// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
	: AARPG_GASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Initialize ASC
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); //Enable replication
	// Send only minal info on GE
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	//Initialize Attribute Set
	HeroAttributeSet = CreateDefaultSubobject<UHeroAttributeSet>("HeroAttributeSet");
}

UAbilitySystemComponent* AHeroCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Guard if this function is called from outside. In normal flow is not needed
	if (HasAuthority())
	{
		InitializeAbilityActorInfo();
		// Generally we don't need to call SetOwner (as it's called on APawn). But we need to be sure (due to Mixed replication)
		// that the ASC Owner is set having the controller as owner
		
		// only on server
		InitializeGAS();
	}
}

void AHeroCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
	InitializeAbilityActorInfo();
}

void AHeroCharacter::InitializeAbilityActorInfo()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		// Initialize who owns the ASC and which actor is being used.
		// Needed so the ASC can access to Avatar, Controller, NetContext etc...
		ASC->InitAbilityActorInfo(this, this);
	}
}

void AHeroCharacter::InitializeGAS()
{
	InitializeAttributes();
	InitializeAbilities();
}

void AHeroCharacter::InitializeUsingGE(FHeroAttributeData* Data) const
{
	// We use a GE to initialize the attributes. to make it work, the GE needs to be properly configured (using proper tag, set to use SetByCaller)
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (Data != nullptr && ASC != nullptr)
	{
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(InitialAttributesEffect, 1.f, GetAbilitySystemComponent()->MakeEffectContext());
		
		if (SpecHandle.IsValid())
		{
			FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
			
			//Set Change attributes. This calls will create a modifier associated with the Attribute Set, defining the magnitude to change
			Spec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("HeroAttributeSet.Health"), Data->Health);
			Spec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("HeroAttributeSet.MaxHealth"), Data->MaxHealth);
			
			// Apply Effect
			ASC->ApplyGameplayEffectSpecToSelf(*Spec);
		}
	}
}

void AHeroCharacter::InitializeByCall(FHeroAttributeData* Data) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (Data != nullptr && ASC != nullptr)
	{
		HeroAttributeSet->InitHealth(Data->Health);
		HeroAttributeSet->InitMaxHealth(Data->MaxHealth);
	}
}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHeroCharacter::InitializeAttributes() const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (ASC != nullptr && HeroAttributeSet != nullptr && HasAuthority())
	{
		//Load Data table with Attribute info
		if (!HeroAttributeData.IsNull())
		{
			// TEXT is related to debug system
			FHeroAttributeData* Data = HeroAttributeData.GetRow<FHeroAttributeData>(TEXT("AHeroCharacter::InitializeAttributes"));
			if (Data != nullptr)
			{
				if (InitialAttributesEffect != nullptr)
				{
					InitializeUsingGE(Data);
				}
				else
				{
					InitializeByCall(Data);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Configured Data Attribute for Hero"));
			}
		}
	}
}

void AHeroCharacter::InitializeAbilities()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (ASC != nullptr && HasAuthority())
	{
		for (const TSubclassOf<UGameplayAbility>& abilityClass : HeroInitialAbilities)
		{
			if (UClass* pAbilityClass = abilityClass.Get())
			{
				FGameplayAbilitySpec abilitySpec(pAbilityClass, 1);
				if (abilitySpec.Ability != nullptr)	// avoiding engine crash
				{
					ASC->GiveAbility(abilitySpec);
				}
			}
		}
	}
	// Here we choose to have a list of abilities. 
	// This can also be done creating a new GE that add the abilities and apply it on initialization (like attributes)
}

