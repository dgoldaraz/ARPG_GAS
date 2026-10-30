// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "UISettings.generated.h"

class UTexture2D;

/**
 * Settings for UI. Used for any info needed when using the UI such images, colors, etc
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="UI Settings"))
class ARPG_GAS_API UUISettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	
	// Map AbilityTag/Image
	UPROPERTY(Config, EditAnywhere, meta = (Category="Ability"))
	TMap<FGameplayTag, TSoftObjectPtr<UTexture2D>> AbilityIcons;
	
	static const UUISettings* Get()
	{
		return GetDefault<UUISettings>();
	}
};
