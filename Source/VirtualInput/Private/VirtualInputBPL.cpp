// Copyright © 2023 AzureuBin. All rights reserved.

#include "VirtualInputBPL.h"

#include "Engine/World.h"
#include "Engine/GameViewportClient.h"
#include "Slate/SGameLayerManager.h"
#include "Framework/Application/SlateApplication.h"

#define PLATFORM_APP	\
	FSlateApplication::Get().GetPlatformApplication()

#define MSG_HANDLER	\
	FSlateApplication::Get().GetPlatformApplication()->GetMessageHandler()

#define CONVERT_TO_MOUSE(Value)	\
	static_cast<EMouseButtons::Type>(Value)

#define GET_KEYCODE(FKey)						\
	const uint32* KeyCodePtr;					\
	const uint32* CharCodePtr;					\
	FInputKeyManager::Get().GetCodesFromKey(FKey, KeyCodePtr, CharCodePtr);	\
	int32 KeyCode = KeyCodePtr ? (int32)*KeyCodePtr : 0;			\
	int32 CharCode = CharCodePtr ? (int32)*CharCodePtr : 0;

void UVirtualInputBPL::TriggerMouseDownEvent(TEnumAsByte<EVirtualMouseButton> MouseKey)
{
	if (!FSlateApplication::IsInitialized())
		return;

	MSG_HANDLER->OnMouseDown(PLATFORM_APP->GetWindowUnderCursor(), CONVERT_TO_MOUSE(MouseKey.GetValue()));
}

void UVirtualInputBPL::TriggerMouseUpEvent(TEnumAsByte<EVirtualMouseButton> MouseKey)
{
	if (!FSlateApplication::IsInitialized())
		return;

	MSG_HANDLER->OnMouseUp(CONVERT_TO_MOUSE(MouseKey.GetValue()));
}

void UVirtualInputBPL::TriggerMouseClicked(TEnumAsByte<EVirtualMouseButton> MouseKey, bool DoubleClick)
{
	if (!FSlateApplication::IsInitialized())
		return;
	
	const EMouseButtons::Type MouseButton = CONVERT_TO_MOUSE(MouseKey.GetValue());
	
	MSG_HANDLER->OnMouseDown(PLATFORM_APP->GetWindowUnderCursor(), MouseButton);
	MSG_HANDLER->OnMouseUp(MouseButton);

	if (DoubleClick)
	{
		MSG_HANDLER->OnMouseDoubleClick(PLATFORM_APP->GetWindowUnderCursor(), MouseButton);
		MSG_HANDLER->OnMouseUp(MouseButton);
	}
}

void UVirtualInputBPL::TriggerMouseMoveEvent(const FVector2D Delta)
{
	if (!FSlateApplication::IsInitialized())
		return;

	MSG_HANDLER->OnRawMouseMove(Delta.X, Delta.Y);
}

void UVirtualInputBPL::SetCursorLocation(UObject* WorldContextObject, FVector2D Location)
{
	if (!FSlateApplication::IsInitialized())
		return;

	FVector2D Absolute = Location;
	const UWorld* World = WorldContextObject->GetWorld();
	if (const TSharedPtr<IGameLayerManager> GameLayerManager = World->GetGameViewport()->GetGameLayerManager())
	{
		Absolute = GameLayerManager->GetViewportWidgetHostGeometry().LocalToAbsolute(Location);
	}

	SetCursorLocationAbsolute(Absolute);
}

void UVirtualInputBPL::SetCursorLocationAbsolute(FVector2D Location)
{
	if (!FSlateApplication::IsInitialized())
		return;

	const TSharedPtr<ICursor> Cursor = FSlateApplication::Get().GetPlatformCursor();
	if (Cursor.IsValid())
	{
		Cursor->SetPosition(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y));
	}
}

void UVirtualInputBPL::TriggerKeyPressed(const FKey Key, const bool bRepeat)
{
	if (!FSlateApplication::IsInitialized())
		return;
	
	GET_KEYCODE(Key)
	MSG_HANDLER->OnKeyDown(KeyCode, CharCode, bRepeat);
	MSG_HANDLER->OnKeyChar(static_cast<TCHAR>(CharCode),bRepeat);
}

void UVirtualInputBPL::TriggerKeyReleased(const FKey Key)
{
	if (!FSlateApplication::IsInitialized())
		return;

	GET_KEYCODE(Key)
	MSG_HANDLER->OnKeyUp(KeyCode, CharCode, false);
}

void UVirtualInputBPL::TriggerKeyClicked(FKey Key)
{
	GET_KEYCODE(Key)
	MSG_HANDLER->OnKeyDown(KeyCode, CharCode, false);
	MSG_HANDLER->OnKeyChar(static_cast<TCHAR>(CharCode),false);
	MSG_HANDLER->OnKeyUp(KeyCode, CharCode, false);
}
