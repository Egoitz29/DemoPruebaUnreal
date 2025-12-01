// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DemoJugable : ModuleRules
{
	public DemoJugable(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG",
			"Slate",
            "Niagara"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DemoJugable",
			"DemoJugable/Variant_Platforming",
			"DemoJugable/Variant_Platforming/Animation",
			"DemoJugable/Variant_Combat",
			"DemoJugable/Variant_Combat/AI",
			"DemoJugable/Variant_Combat/Animation",
			"DemoJugable/Variant_Combat/Gameplay",
			"DemoJugable/Variant_Combat/Interfaces",
			"DemoJugable/Variant_Combat/UI",
			"DemoJugable/Variant_SideScrolling",
			"DemoJugable/Variant_SideScrolling/AI",
			"DemoJugable/Variant_SideScrolling/Gameplay",
			"DemoJugable/Variant_SideScrolling/Interfaces",
			"DemoJugable/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
