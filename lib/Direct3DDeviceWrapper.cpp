#include "Direct3DDeviceWrapper.h"

#include <iostream>

IDirect3DDevice9* Direct3DDeviceWrapper::d3dDevice = nullptr;
IDirect3D9* Direct3DDeviceWrapper::direct3D9 = nullptr;
LPD3DXSPRITE Direct3DDeviceWrapper::sprite = nullptr;

using namespace std;

//Static class no constructor and destructor
void Direct3DDeviceWrapper::CleanUp()
{
    if (sprite)
    {
        sprite->Release();
        sprite = nullptr;
    }
    if (d3dDevice)
    {
        d3dDevice->Release();
        d3dDevice = NULL;
    }
    if (direct3D9)
    {
        direct3D9->Release();
        direct3D9 = NULL;
    }
}


//d3dDevice begin scene and sprite begin
void Direct3DDeviceWrapper::BeginRender()
{
    // Start rendering a frame
    if (d3dDevice)
    {
        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        d3dDevice->BeginScene();
        if (sprite)
        {
            sprite->Begin(D3DXSPRITE_ALPHABLEND);
        }

    }
}

//d3dDevice sprite end and end scene 
void Direct3DDeviceWrapper::EndRender()
{
    // End rendering a frame
    if (d3dDevice)
    {
        if (sprite)
        {
            sprite->End();
        }
        d3dDevice->EndScene();
        d3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}

IDirect3DDevice9* Direct3DDeviceWrapper::GetDevice()
{
    // Check if d3dDevice is not null before returning it
    if (d3dDevice != nullptr)
    {
        return d3dDevice;
    }
    else
    {
        return nullptr;
    }
}

//Create device
//After create device create Sprite
bool Direct3DDeviceWrapper::CreateDevice(int screenWidth, int screenHeight, HWND hWnd)
{
    //	Define Direct3D 9.
    direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

    //	Define how the screen presents.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    // Configure other device parameters such as window size, fullscreen mode, etc.
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = screenWidth;
    d3dpp.BackBufferHeight = screenHeight;
    d3dpp.hDeviceWindow = hWnd;

    //	Create a Direct3D 9 device.
    HRESULT hr = direct3D9->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3dDevice);

    if (FAILED(hr))
    {
        // Handle the case of device creation failure
        return false;
    }

    //After creating d3dDevice create sprite to render game object
    InitializeSpriteBrush(d3dDevice);

    return true;
}


//Set sprite
void Direct3DDeviceWrapper::SetSprite(LPD3DXSPRITE newSprite)
{
    sprite = newSprite;
}

//Initialize sprite
void Direct3DDeviceWrapper::InitializeSpriteBrush(IDirect3DDevice9* d3ddevice)
{
    if (d3ddevice)
    {
        HRESULT hr = D3DXCreateSprite(d3ddevice, &sprite);
        if (FAILED(hr))
        {
            sprite = nullptr;
        }
    }
}

//For every game state to initialize texture
void Direct3DDeviceWrapper::LoadTextureFromFile(const char* filename, LPDIRECT3DTEXTURE9& texture)
{
    if (texture == nullptr)
    {
        if (d3dDevice != nullptr)
        {
            HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, filename, &texture);
        }
    }
}


void Direct3DDeviceWrapper::setSpriteBrushTransform(D3DXMATRIX objectMatrix) {
    sprite->SetTransform(&objectMatrix);

}

//For game object to render
void Direct3DDeviceWrapper::DrawSprite(LPDIRECT3DTEXTURE9 texture, RECT& sourceRect, const D3DCOLOR& color)
{
    if (d3dDevice != nullptr && sprite != nullptr)
    {
        // Check if sourceRect is empty
        if (IsRectEmpty(&sourceRect))
        {
            // If it's an empty rectangle, set it to NULL
            sprite->Draw(texture, NULL, NULL, NULL, color);
        }
        else
        {
            // If it's not an empty rectangle, use the provided sourceRect
            sprite->Draw(texture, &sourceRect, NULL, NULL, color);
        }
    }
}
