// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HeroBaseAbility.generated.h"

/**
 * Base ability used in Hero game. Allow generic accesses logic equal to all abilities in game
 */
UCLASS()
class ARPG_GAS_API UHeroBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	// Return Cooldown tag
	virtual FGameplayTag GetCoolDownTag() const;
	
protected:
	
	// Cool Down associated tag (if any) to an ability
	UPROPERTY(EditAnywhere)
	FGameplayTag CoolDownTag;
};
