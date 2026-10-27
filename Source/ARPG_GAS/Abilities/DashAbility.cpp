// Fill out your copyright notice in the Description page of Project Settings.


#include "DashAbility.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "GameFramework/RootMotionSource.h"
#include "ARPGTags.h"

UDashAbility::UDashAbility()
{
	//Set Ability info
	// TODO: Create global file to store all tags, so access is not based on String
	FGameplayTag dashTag = GTags::DashAbility;
	AbilityTags.AddTag(dashTag);
	ActivationBlockedTags.AddTag(dashTag);
	
}

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// Create animation Task and wait to end
		// Todo: Define rate based on speed attribute?
		// TODO: Use input to define animation?
		m_AnimationTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DashAnimationTask"),MontageToPlay);
		m_AnimationTask->ReadyForActivation();
		// TODO: Use input to define movement.
		FVector Direction = GetOwningActorFromActorInfo()->GetActorForwardVector();
		FVector CurrentSpeed = GetOwningActorFromActorInfo()->GetVelocity();
		
		m_RootMotionConstantForce = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, FName(), Direction, DashStrength,
			DashDuration, false,nullptr, ERootMotionFinishVelocityMode::SetVelocity, CurrentSpeed, 0.0f, false);
		
		m_RootMotionConstantForce->OnFinish.AddUniqueDynamic(this, &UDashAbility::OnMovementDone);
		m_RootMotionConstantForce->ReadyForActivation();
		// TODO: Base on Level, create a parry effect
	}
}

void UDashAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDashAbility::OnMovementDone()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
