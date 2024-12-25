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
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorGCButtonStyle::Initialize();
	FEditorGCButtonStyle::ReloadTextures();

	FEditorGCButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorGCButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FEditorGCButtonModule::PluginButtonClicked),
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

void FEditorGCButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEditorGCButtonCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorGCButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorGCButtonModule, EditorGCButton)