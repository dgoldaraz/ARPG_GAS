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

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize attreibutes on game starts
	InitializeAttributes();
	
	InitializeAbilities();
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHeroCharacter::InitializeAttributes()
{
	if (GetAbilitySystemComponent() != nullptr && HeroAttributeSet != nullptr)
	{
		//Load Data table with Attribute info
		if (!HeroAttributeData.IsNull())
		{
			FHeroAttributeData* Data = HeroAttributeData.GetRow<FHeroAttributeData>("");
			if (Data != nullptr)
			{
				//  Create Init GE. This GE needs to be created on Editor.
				// On it, we need to add different Modifiers per attribute, setting the Magnitude Calculation Type to SetByCaller
				// And matching the attribute to call with a GameplayTag
				TSubclassOf<UGameplayEffect> InitGE = LoadClass<UGameplayEffect>(nullptr, TEXT("/Game/Abilities/GE_InitAttributes.GE_InitAttributes_C"));
				if (InitGE == nullptr)
				{
					UE_LOG(LogTemp, Error, TEXT("No Init GE GE_InitAttributes"));
					return;
				}
				
				FGameplayEffectSpecHandle SpecHandle =GetAbilitySystemComponent()->MakeOutgoingSpec(InitGE, 1.f, GetAbilitySystemComponent()->MakeEffectContext());
			
				if (SpecHandle.IsValid())
				{
					FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
					
					//Set Change attributes. This calls will create a modifier associated with the Attribute Set, defining the magnitude to change
					FGameplayTag tag = FGameplayTag::RequestGameplayTag("HeroAttributeSet.Health");
					Spec->SetSetByCallerMagnitude(tag, 150.0f);
					Spec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("HeroAttributeSet.MaxHealth"), Data->MaxHealth);
					
					// Apply Effect
					GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*Spec);
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
	// Here we choose to have a list of abiltiies. 
	// This can also be done creating a new GE that add the abilities and apply it on initialization (like attributes)
	for (const TSubclassOf<UGameplayAbility>& abilityClass : HeroInitialAbilities)
	{
		if (UClass* pAbilityClass = abilityClass.Get())
		{
			FGameplayAbilitySpec abilitySpec(pAbilityClass);
			if (abilitySpec.Ability != nullptr)	// avoiding engine crash
			{
				GetAbilitySystemComponent()->GiveAbility(abilitySpec);
			}
		}
	}
}

