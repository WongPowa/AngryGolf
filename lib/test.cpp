
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
//	include the Direct3D 9 library
#include <d3d9.h>
//	include the D3DX9 library (sprite)
#include <d3dx9.h>
//  include the Direct Input library
#include <dinput.h>

#include "GameObject.h"
#include "GameLv1.h"

//#pragma comment(lib,"dinput8.lib")
//#pragma comment(lib,"dxguid.lib")
using namespace std;


//------------------------------------------------Control Variable-----------------------------------------------------------
//Control screen performance
#define screenWidth 1440
#define screenHeight 900

//Control fullscreen, false == not fullscreen
bool fullScreen = true;




//------------------------------------------------Global Variable------------------------------------------------------------
HWND g_hWnd = NULL;
//Make global to use when createWindow()
WNDCLASS wndClass;

//For d3dpp device
IDirect3D9* direct3D9;
IDirect3DDevice9* d3dDevice;

//Direct Input device
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
BYTE* diKeys;

//Sprite Brush and texture
//LPDIRECT3DTEXTURE9 texture = NULL;
LPD3DXSPRITE sprite = NULL;

LPDIRECT3DTEXTURE9 textureBackground = NULL;


//FONT
LPD3DXFONT fontGameTitle = NULL;
RECT fontRect;






GameLv1* gameLv1 = nullptr;





//------------------------------------------------Declare function-----------------------------------------------------------
//Create basic window format
bool createWindow(HINSTANCE hInstance);
void cleanUpWindow(HINSTANCE hInstance);
bool windowIsRunning(HINSTANCE hInstance);

//Create d3dpp dvice
bool createD3D9(bool fullScreen);

//Cleaning up
void cleanUpAll(HINSTANCE hInstance);



LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//------------------------------------------------Define function-------------------------------------------------------------
bool createWindow(HINSTANCE hInstance) {

	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	/*
	Step 2
	Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Angry GOLF", WS_OVERLAPPEDWINDOW, 0, 0, screenWidth, screenHeight, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	if (!g_hWnd)
	{
		MessageBox(g_hWnd, "Invalid Window Handle", NULL, MB_OK);
		return false;
	}
	else
	{
		return true;
	}

	//ShowCursor(false);

}
bool windowIsRunning(HINSTANCE hInstance) {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//	Receive a quit message
			if (msg.message == WM_QUIT)
			{
				return false;
			}
			//	Translate the message 
			TranslateMessage(&msg);
			//	Send message to your window procedure
			DispatchMessage(&msg);
		}
		return true;
	}


}

void initializeGame() {

	//Initialize Background
	HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
	hr = D3DXCreateTextureFromFile(d3dDevice, "Image/Background Night.jpg", &textureBackground);

	//Small validation check
	
	if (FAILED(hr)) {
		MessageBox(g_hWnd, "Failed to load texture", NULL, MB_OK);
	}
	
}



//Cleaning
void cleanUpAll(HINSTANCE hInstance) {

	//Release
	if (sprite != nullptr) {
		sprite->Release();
		sprite = NULL;
	}

	if (textureBackground != nullptr) {
		textureBackground->Release();
		textureBackground = NULL;
	}

	if (fontGameTitle != nullptr) {
		fontGameTitle->Release();
		fontGameTitle = NULL;
	}



	//Clean Up 
	//Release diKeys
	delete[] diKeys;

	//Release Input Keyboard Device
	if (dInputKeyboardDevice) {
		dInputKeyboardDevice->Unacquire();
		dInputKeyboardDevice->Release();
		dInputKeyboardDevice = NULL;
	}

	//	Release DirectInput.
	if (dInput) {
		dInput->Release();
		dInput = NULL;
	}
	if (d3dDevice) {
		d3dDevice->Release();
		d3dDevice = NULL;
	}

	if (direct3D9) {
		direct3D9->Release();
		direct3D9 = NULL;
	}
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}


//------------------------------------------------------Main--------------------------------------------------------------------
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Create Window
	if (createWindow(hInstance))
	{
		//Create DirectX 
		//	Define Direct3D 9.
		//Small validation check
		if (NULL == (direct3D9 = Direct3DCreate9(D3D_SDK_VERSION)))
		{
			MessageBox(g_hWnd, "Define D3D9 Failed!!", NULL, MB_OK);
			return false;
		}

		//	Define how the screen presents.
		D3DPRESENT_PARAMETERS d3dPP;
		ZeroMemory(&d3dPP, sizeof(d3dPP));

		//	Refer to Direct3D 9 documentation for the meaning of the members.
		d3dPP.Windowed = true;
		d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dPP.BackBufferCount = 1;
		d3dPP.BackBufferWidth = screenWidth;
		d3dPP.BackBufferHeight = screenHeight;
		d3dPP.hDeviceWindow = g_hWnd;

		//	Create a Direct3D 9 device.
		HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

		if (FAILED(hr))
		{
			MessageBox(g_hWnd, "Create D3D9 Failed!!", NULL, MB_OK);
			return false;
		}

	}
	else {
		//	To Do: Cout out the message to indicate the failure.
		MessageBox(g_hWnd, "Create Window Failed!!", NULL, MB_OK);
	}


	if (d3dDevice != nullptr) {
		gameLv1 = new GameLv1(d3dDevice);
	}

	HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
	if (FAILED(hr)) {
		MessageBox(g_hWnd, "Failed to load sprite", NULL, MB_OK);
	}

	gameLv1->initialize(g_hWnd);

	while (windowIsRunning(hInstance))
	{


		if (NULL == d3dDevice) {
			MessageBox(g_hWnd, "d3dDevice is NULL!!", NULL, MB_OK);
			return false;
		}

		d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3dDevice->BeginScene();


		//	To Do:
		//	Drawing.
		//And all Calculation do at here
		if (sprite != nullptr) {
			sprite->Begin(D3DXSPRITE_ALPHABLEND);

			//Draw Background
			//sprite->Draw(textureBackground, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

			gameLv1->Render(sprite);



			sprite->End();
		}







		d3dDevice->EndScene();
		d3dDevice->Present(NULL, NULL, NULL, NULL);



	}



	//Clean Up Everything
	cleanUpAll(hInstance);

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------