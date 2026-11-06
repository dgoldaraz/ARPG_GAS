// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GTags
{
	// Input
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionUp);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionDown);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionRight);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionLeft);
	
	// Abilities
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DashAbility);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DashState);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DashCooldown);
	
	// Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeMaxHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeStamina);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeMaxStamina);
}
