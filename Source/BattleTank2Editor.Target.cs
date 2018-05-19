// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTank2EditorTarget : TargetRules
{
	public BattleTank2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.Add("BattleTank2");
	}

	//
	// TargetRules interface.
	//

	// public override void SetupBinaries(
	// 	TargetInfo Target,
	// 	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	// 	ref List<string> OutExtraModuleNames
	// 	)
	// {
	// 	OutExtraModuleNames.AddRange( new string[] { "BattleTank2" } );
	// }
}
