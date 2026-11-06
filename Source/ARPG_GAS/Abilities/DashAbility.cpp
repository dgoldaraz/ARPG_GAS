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
	// Allows that clients activate the ability immediately and the server approve it
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy =EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// Create animation Task and wait to end
		m_AnimationTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DashAnimationTask"),MontageToPlay);
		m_AnimationTask->ReadyForActivation();
		// TODO: Properly define how moevement is going to be done
		// For now just use prefixed values
		// in the future we can use MorphWarping or a value based on Stamina/Other Values + Speed + Level
		
		FVector Direction = GetOwningActorFromActorInfo()->GetActorForwardVector();
		FVector CurrentSpeed = GetOwningActorFromActorInfo()->GetVelocity();
		
		m_RootMotionConstantForce = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, FName(), Direction, DashStrength,
			DashDuration, false,nullptr, ERootMotionFinishVelocityMode::SetVelocity, CurrentSpeed, 0.0f, false);
		
		m_RootMotionConstantForce->OnFinish.AddUniqueDynamic(this, &UDashAbility::OnMovementDone);
		m_AnimationTask->OnCancelled.AddUniqueDynamic(this, &UDashAbility::OnMovementDone);
		m_AnimationTask->OnInterrupted.AddUniqueDynamic(this, &UDashAbility::OnMovementDone);
		
		m_RootMotionConstantForce->ReadyForActivation();
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
