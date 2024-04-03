// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_Dong_Port_02 : ModuleRules
{
	public UE5_Dong_Port_02(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
            "AnimGraphRuntime",
            "Niagara",
			"UMG"
        });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
