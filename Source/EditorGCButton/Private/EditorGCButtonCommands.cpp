// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorGCButtonCommands.h"

#define LOCTEXT_NAMESPACE "FEditorGCButtonModule"

void FEditorGCButtonCommands::RegisterCommands()
{
	UI_COMMAND(CollectGarbageAction, "EditorGCButton", "Collect garbage", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ReloadSlateResourcesAction, "ReloadSlateResources", "Reload Slate Resources", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
