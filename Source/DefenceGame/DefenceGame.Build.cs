// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DefenceGame : ModuleRules
{
	public DefenceGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore" ,
            "StoneToolClass" ,
            "Slate",
            "SlateCore",
            "SimpleScreenLoading",
            "SimpleTutorials",
            "SimpleArchives",
            "SimpleGameSettings",
            "SimpleTutorials",
            "ApexDestruction",
            "AIModule",
            "SimpleDrawText",
            "RawMesh",  //添加原始模型数据模块
           // "GeometryAlgorithms"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
