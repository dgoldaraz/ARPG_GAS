// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ARPG_GAS : ModuleRules
{
	public ARPG_GAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ARPG_GAS",
			"ARPG_GAS/Variant_Platforming",
			"ARPG_GAS/Variant_Platforming/Animation",
			"ARPG_GAS/Variant_Combat",
			"ARPG_GAS/Variant_Combat/AI",
			"ARPG_GAS/Variant_Combat/Animation",
			"ARPG_GAS/Variant_Combat/Gameplay",
			"ARPG_GAS/Variant_Combat/Interfaces",
			"ARPG_GAS/Variant_Combat/UI",
			"ARPG_GAS/Variant_SideScrolling",
			"ARPG_GAS/Variant_SideScrolling/AI",
			"ARPG_GAS/Variant_SideScrolling/Gameplay",
			"ARPG_GAS/Variant_SideScrolling/Interfaces",
			"ARPG_GAS/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
