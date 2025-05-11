// DirectInput.cpp
#include "DirectInput.h"
#include <iostream>
using namespace std;

LPDIRECTINPUT8 DirectInput::dInput = nullptr;
LPDIRECTINPUT8 DirectInput::dMouseInput = nullptr;
LPDIRECTINPUTDEVICE8 DirectInput::dInputKeyboardDevice = nullptr;
LPDIRECTINPUTDEVICE8 DirectInput::dInputMouseDevice = nullptr;
BYTE* DirectInput::diKeys = nullptr;
DIMOUSESTATE DirectInput::mouseState;
int DirectInput::mouseX = 0;
int DirectInput::mouseY = 0;
bool DirectInput::IsMouseButtonDown = false;

void DirectInput::Initialize(HWND g_hWnd) {
    HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
    if (FAILED(hr))
        MessageBox(g_hWnd, "Failed to Create Direct Input", NULL, MB_OK);

    // Create the keyboard device.
    hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

    if (FAILED(hr))
        MessageBox(g_hWnd, "Failed to Create Keyboard Device", NULL, MB_OK);

    // Set the input data format.
    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

    // Set the cooperative level.
    dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE);

    // Acquire the device.
    dInputKeyboardDevice->Acquire();

    // Key input buffer
    diKeys = new byte[256];

    hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dMouseInput, NULL);

    hr = dMouseInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

    if (FAILED(hr))
        MessageBox(g_hWnd, "Failed to Create Mouse Device", NULL, MB_OK);

    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

    dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE);

    // Acquire the device.
    dInputMouseDevice->Acquire();
}

void DirectInput::Release() {
    // Release diKeys
    delete[] diKeys;
    diKeys = nullptr;

    // Release Input Keyboard Device
    if (dInputKeyboardDevice) {
        dInputKeyboardDevice->Unacquire();
        dInputKeyboardDevice->Release();
        dInputKeyboardDevice = NULL;
    }

    if (dInputMouseDevice) {
        dInputMouseDevice->Unacquire();
        dInputMouseDevice->Release();
        dInputMouseDevice = NULL;
    }

    // Release DirectInput.
    if (dInput) {
        dInput->Release();
        dInput = NULL;
    }

    if (dMouseInput) {
        dMouseInput->Release();
        dMouseInput = NULL;
    }
}

bool DirectInput::getKeyboardInput() {
    dInputKeyboardDevice->GetDeviceState(256, diKeys);

    if (diKeys[DIK_UP] & 0x80) {
        return true;
    }

    if (diKeys[DIK_DOWN] & 0x80) {
        return true;
    }

    if (diKeys[DIK_LEFT] & 0x80) {
        return true;
    }

    if (diKeys[DIK_RIGHT] & 0x80) {
        return true;
    }

    return false;
}

bool DirectInput::getMouseInput() {
    dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

    if (BUTTONDOWN(mouseState, 0)) {
        IsMouseButtonDown = true;
        return true;
    }
    IsMouseButtonDown = false;
    return false;
}

void DirectInput::setMousePosition(POINT cursorPos)
{
    mouseX = cursorPos.x;
    mouseY = cursorPos.y;

}


int DirectInput::getMousePositionX() {
    return mouseX;
}

int DirectInput::getMousePositionY() {
    return mouseY;
}

bool DirectInput::getIsMouseButtonDown()
{
    return IsMouseButtonDown;
}
