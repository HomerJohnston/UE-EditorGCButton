// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorGCButtonStyle.h"
#include "EditorGCButton.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FEditorGCButtonStyle::StyleInstance = nullptr;

void FEditorGCButtonStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FEditorGCButtonStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FEditorGCButtonStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("EditorGCButtonStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FEditorGCButtonStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("EditorGCButtonStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("EditorGCButton")->GetBaseDir() / TEXT("Resources"));
	Style->Set("EditorGCButton.PluginAction", new IMAGE_BRUSH_SVG(TEXT("EditorGCButton"), Icon20x20));
	return Style;
}

void FEditorGCButtonStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FEditorGCButtonStyle::Get()
{
	return *StyleInstance;
}
