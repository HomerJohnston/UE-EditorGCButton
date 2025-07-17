// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorGCButton.h"
#include "EditorGCButtonStyle.h"
#include "EditorGCButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "UObject/UObjectGlobals.h"

static const FName EditorGCButtonTabName("EditorGCButton");

#define LOCTEXT_NAMESPACE "FEditorGCButtonModule"

void FEditorGCButtonModule::StartupModule()
{
	// Initialize our style
	FEditorGCButtonStyle::Initialize();

	// Initialize our commands container
	FEditorGCButtonCommands::Register();

	// Setup our master command-actions list
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorGCButtonCommands::Get().CollectGarbageAction,
		FExecuteAction::CreateRaw(this, &FEditorGCButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FEditorGCButtonCommands::Get().ReloadSlateResourcesAction,
		FExecuteAction::CreateRaw(this, &FEditorGCButtonModule::ReloadSlateResourcesClicked),
		FCanExecuteAction());
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEditorGCButtonModule::RegisterMenus));
}

void FEditorGCButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEditorGCButtonStyle::Shutdown();

	FEditorGCButtonCommands::Unregister();
}

void FEditorGCButtonModule::PluginButtonClicked()
{
	CollectGarbage(EObjectFlags::RF_NoFlags);
}

void FEditorGCButtonModule::ReloadSlateResourcesClicked()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

void FEditorGCButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry1 = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorGCButtonCommands::Get().CollectGarbageAction));
				FToolMenuEntry& Entry2 = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorGCButtonCommands::Get().ReloadSlateResourcesAction));
				Entry1.SetCommandList(PluginCommands);
				Entry2.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorGCButtonModule, EditorGCButton)