#pragma once
#include <dinput.h>
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

class DirectInput
{
public:
    static bool getKeyboardInput();
    static bool getMouseInput();
    static void setMousePosition(POINT cursorPos);
    static int getMousePositionX();
    static int getMousePositionY();
    static bool getIsMouseButtonDown();

    static void Initialize(HWND g_hWnd);
    static void Release();

private:
    static LPDIRECTINPUT8 dInput;
    static LPDIRECTINPUT8 dMouseInput;
    static LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
    static LPDIRECTINPUTDEVICE8 dInputMouseDevice;
    static BYTE* diKeys;
    static DIMOUSESTATE mouseState;
    static int mouseX; // Store current mouse position X
    static int mouseY; // Store current mouse position Y
    static bool IsMouseButtonDown;

};