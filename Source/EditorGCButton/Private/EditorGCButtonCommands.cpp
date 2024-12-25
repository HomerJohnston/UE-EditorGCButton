// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorGCButtonCommands.h"

#define LOCTEXT_NAMESPACE "FEditorGCButtonModule"

void FEditorGCButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "EditorGCButton", "Collect garbage", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
