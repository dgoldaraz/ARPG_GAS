// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGTags.h"

namespace GTags
{
	// Input
	UE_DEFINE_GAMEPLAY_TAG(InputActionUp, "InputTag.Ability.ActionUp");
	UE_DEFINE_GAMEPLAY_TAG(InputActionDown, "InputTag.Ability.ActionDown");
	UE_DEFINE_GAMEPLAY_TAG(InputActionRight, "InputTag.Ability.ActionRight");
	UE_DEFINE_GAMEPLAY_TAG(InputActionLeft, "InputTag.Ability.ActionLeft");
	
	// Abilities
	UE_DEFINE_GAMEPLAY_TAG(DashAbility, "HeroAbilities.Dash");
	UE_DEFINE_GAMEPLAY_TAG(DashState, "State.Dashing");
	UE_DEFINE_GAMEPLAY_TAG(DashCooldown, "State.CooldownDash");
	
	// Attributes
	UE_DEFINE_GAMEPLAY_TAG(AttributeMaxStamina, "HeroAttributeSet.MaxStamina");
	UE_DEFINE_GAMEPLAY_TAG(AttributeHealth, "HeroAttributeSet.Health");
	UE_DEFINE_GAMEPLAY_TAG(AttributeMaxHealth, "HeroAttributeSet.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(AttributeStamina, "HeroAttributeSet.Stamina");
	
	
}