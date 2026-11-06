// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroBaseAbility.h"
#include "DashAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;
class UAbilityTask_ApplyRootMotionConstantForce;

/**
 * Ability for handle a Dash action. Moving quick in one direction
 * Possible improvements:
 * - Add input directed Dash
 * - Add perfect dodge 
 */
UCLASS()
class ARPG_GAS_API UDashAbility : public UHeroBaseAbility
{
	GENERATED_BODY()
	
public:
	
	UDashAbility();
	
	// Override UGameplayAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// End Override UGameplayAbility
protected:
	
	// Called when RT movement is completed
	UFUNCTION()
	void OnMovementDone();
	
protected:
	
	// Dash Montage
	UPROPERTY(EditAnywhere, Category = "Dash")
	TObjectPtr<UAnimMontage> MontageToPlay;
	
	// Root motion Properties
	// RootMotion movement strenght
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashStrength = 500.0f;
	
	// RT duration
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashDuration = 0.2f;
	
private:
	
	UPROPERTY(Transient)
	TObjectPtr<UAbilityTask_PlayMontageAndWait> m_AnimationTask = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<UAbilityTask_ApplyRootMotionConstantForce> m_RootMotionConstantForce = nullptr;
};
