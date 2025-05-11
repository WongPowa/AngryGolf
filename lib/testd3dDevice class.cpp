
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
//	include the Direct3D 9 library
#include <d3d9.h>
//	include the D3DX9 library (sprite)
#include <d3dx9.h>
//  include the Direct Input library
#include <dinput.h>
//	include the GameObject header
#include "Direct3DDeviceWrapper.h"
#include "GameObject.h"
#include "PlayerControlledObject.h"
#include "GameLv1.h"

//#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
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

//For d3dpp device class
Direct3DDeviceWrapper* d3dDeviceWrapper = nullptr;

//Direct Input device
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
BYTE* diKeys;

//Sprite Brush and texture
//LPDIRECT3DTEXTURE9 texture = NULL;
LPD3DXSPRITE sprite = NULL;



//------------------------------------------------Initialize Game Object-----------------------------------------------------

//PlayerControlledObject golf;
//Mainmenu mainMenu;
GameLv1* gameLv1 = nullptr;
//GameLv2 gameLv2;
//GameOver gameOver;




//------------------------------------------------Declare function-----------------------------------------------------------
//Create basic window format
bool createWindow(HINSTANCE hInstance);
void cleanUpWindow(HINSTANCE hInstance);
bool windowIsRunning(HINSTANCE hInstance);
bool render();

//Initialize (with sprtie)
void initializeGame();
void initializeGameObject();


//Create Input
BYTE* createDXKeyboardInput();
void getInput(BYTE* diKeys);
void cleanUpDI();

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


//Create direct input
BYTE* createDXKeyboardInput() {

	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE);

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();

	//	Key input buffer
	BYTE* diKeys = new byte[256];

	return diKeys;

}

void initializeGame() {

	//Initialize Background
	HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);
	hr = D3DXCreateTextureFromFile(d3dDevice, "Image/Background Night.jpg", &textureBackground);


	if (d3dDevice != nullptr) {
		gameLv1 = new GameLv1(d3dDevice);
	}

	//Initialize Game Object
	initializeGameObject();
}


void initializeGameObject() {
	//MainMenu.initialize();
	if (gameLv1 != nullptr) {
		gameLv1->initialize();
	}


	//Initialize Normal Game Object
}

//Get Input
void getInput(BYTE* diKeys) {
	//Can use enum here if want


	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);


	if (diKeys[DIK_UP] & 0x80)
	{
		cout << "UP" << endl;
	}

	if (diKeys[DIK_DOWN] & 0x80)
	{
		cout << "DOWN" << endl;
	}

	if (diKeys[DIK_LEFT] & 0x80)
	{
		cout << "LEFT" << endl;
	}

	if (diKeys[DIK_RIGHT] & 0x80)
	{
		cout << "RIGHT" << endl;
	}



}


//Cleaning
void cleanUpAll(HINSTANCE hInstance) {

	//Release
	if (sprite != nullptr) {
		sprite->Release();
		sprite = NULL;
	}


	gameLv1->Release();


	//Clean Up 
	cleanUpDI();
	//Delete object, will call detructor to release and point to nullptr
	//	cleanUpD3D9();
	delete d3dDeviceWrapper;
	cleanUpWindow(hInstance);
}
void cleanUpDI() {

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

}
void cleanUpWindow(HINSTANCE hInstance) {
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool render() {
	
	//Begin scene
	d3dDeviceWrapper->BeginRender();



	//	To Do:
	//	Drawing.
	//And all Calculation do at here

	if (sprite != nullptr) {
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		gameLv1->Render(sprite);



		//Set FONT align to center
		/**
		int textWidth = 400;
		int textHeight = 200;

		int left = (screenWidth - textWidth) / 2;
		int top = (screenHeight - textHeight) / 2;

		SetRect(&fontRect, left, top, left + textWidth, top + textHeight);

		fontGameTitle->DrawText(sprite, "ANGRY GOLF", -1, &fontRect, 0, D3DCOLOR_XRGB(255, 255, 255));
		*/







		sprite->End();
	}

	//End scene
	d3dDeviceWrapper->EndRender();

}








//------------------------------------------------------Main--------------------------------------------------------------------
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Create Window
	if (createWindow(hInstance))
	{
		//Create Direct3D Device 
		Direct3DDeviceWrapper* d3dDeviceWrapper = new Direct3DDeviceWrapper(g_hWnd);
		if (d3dDeviceWrapper->ConfigureDeviceParameters(screenWidth, screenHeight) && d3dDeviceWrapper->CreateDevice()) {

			//Create Dinput device

		}
	}
	else {
		//	To Do: Cout out the message to indicate the failure.
		MessageBox(g_hWnd, "Create Window Failed!!", NULL, MB_OK);
	}

	//Create Direct Input Device
	diKeys = createDXKeyboardInput();


	//Initialize and load the texture before enter the game
	initializeGame();


	while (windowIsRunning(hInstance))
	{
		getInput(diKeys);
		// Update();
		render();



	}



	//Clean Up Everything
	cleanUpAll(hInstance);

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------