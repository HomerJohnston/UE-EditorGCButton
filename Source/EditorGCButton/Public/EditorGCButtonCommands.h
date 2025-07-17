// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorGCButtonStyle.h"

class FEditorGCButtonCommands : public TCommands<FEditorGCButtonCommands>
{
public:

	FEditorGCButtonCommands()
		: TCommands<FEditorGCButtonCommands>(TEXT("EditorGCButton"), NSLOCTEXT("Contexts", "EditorGCButton", "EditorGCButton Plugin"), NAME_None, FEditorGCButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > CollectGarbageAction;
	TSharedPtr< FUICommandInfo > ReloadSlateResourcesAction;
};
