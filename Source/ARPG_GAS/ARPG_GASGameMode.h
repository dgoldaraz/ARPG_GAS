// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ARPG_GASGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AARPG_GASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AARPG_GASGameMode();
};



