// Copyright © 2023 AzureuBin. All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "VirtualInputBPL.generated.h"


UENUM()
enum EVirtualMouseButton
{
	LeftButton = 0,
	MiddleButton,
	RightButton,
	ThumbButton,
	Thumb2Button,
};

/* 
*	Virtual Input Function Library
*/
UCLASS()
class UVirtualInputBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Mouse Button Down"))
	static void TriggerMouseDownEvent(TEnumAsByte<EVirtualMouseButton> MouseKey);

	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Mouse Button Up"))
	static void TriggerMouseUpEvent(TEnumAsByte<EVirtualMouseButton> MouseKey);

	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Mouse Button Clicked"))
	static void TriggerMouseClicked(TEnumAsByte<EVirtualMouseButton> MouseKey, bool DoubleClick);

	/* May just work when left mouse button was pressed */
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Mouse Move"))
	static void TriggerMouseMoveEvent(FVector2D Delta);

	/* Set Cursor location in Viewport Space */
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Set Cursor Location (Viewport)", WorldContext="WorldContextObject"))
	static void SetCursorLocation(UObject* WorldContextObject, FVector2D Location);

	/* Set Cursor location in Absolute Space */
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Set Cursor Location (Absolute)"))
	static void SetCursorLocationAbsolute(FVector2D Location);

	/* Note that using this function to trigger mouse events will not affect Slate. */
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Key Pressed"))
	static void TriggerKeyPressed(const FKey Key, bool bRepeat);

	/* Note that using this function to trigger mouse events will not affect Slate. */
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Key Released"))
	static void TriggerKeyReleased(const FKey Key);

	/* Note that using this function to trigger mouse events will not affect Slate. */
	UFUNCTION(BlueprintCallable, Category="Virtual Input", meta=(DisplayName="Dummy Key Click"))
	static void TriggerKeyClicked(const FKey Key);
};

