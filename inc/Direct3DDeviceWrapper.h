#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Direct3DDeviceWrapper
{
public:

    static void BeginRender();
    static void EndRender();
    static bool CreateDevice(int screenWidth, int screenHeight, HWND hWnd);
    static IDirect3DDevice9* GetDevice();

    static void SetSprite(LPD3DXSPRITE newSprite);
    static void InitializeSpriteBrush(IDirect3DDevice9* d3dDevice);
    static void setSpriteBrushTransform(D3DXMATRIX objectMatrix);
    static void DrawSprite(LPDIRECT3DTEXTURE9 texture, RECT& sourceRect, const D3DCOLOR& color);
    static void LoadTextureFromFile(const char* filename, LPDIRECT3DTEXTURE9& texture);
    static void CleanUp();

private:
    static IDirect3D9* direct3D9;
    static IDirect3DDevice9* d3dDevice;
    static LPD3DXSPRITE sprite;
};