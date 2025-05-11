
#define WIN32_LEAN_AND_MEAN
#include <iostream>
//	include the Direct3D 9 library
#include <d3d9.h>
//	include the D3DX9 library (sprite)
#include <d3dx9.h>
//  include the Direct Input library
#include <dinput.h>
//	include the GameObject header
#include "Direct3DDeviceWrapper.h"
#include "PlayerControlledObject.h"
#include "EnemyObject.h" 
#include "GameStateManager.h"
#include "common.h"
#include "FrameTimer.h"
#include "Physics.h"
#include "GameLv1.h"
#include "MainMenu.h"
#include "DirectInput.h"
#include "AudioManager.h"

//#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
//#pragma comment(lib,"dinput8.lib")
//#pragma comment(lib,"dxguid.lib")
using namespace std;


//------------------------------------------------Control Variable-----------------------------------------------------------
//Control screen performance
#define screenWidth 1000
#define screenHeight 600



//------------------------------------------------Global Variable------------------------------------------------------------
HWND g_hWnd = NULL;
//Make global to use when createWindow()
WNDCLASS wndClass;

//CursorPos
POINT cursorPos;

//Timer
FrameTimer myTimer;

//Sound
//AudioManager* sounds;

//Physics
Physics physics(0.99f, 0.5f, 0.05f);
float gravity = 0.5f;
float airResForce = 0.99f;



//------------------------------------------------Initialize Game Object-----------------------------------------------------
GameState* gameState = nullptr;
//GameLv2 gameLv2;
//GameOver gameOver;


//------------------------------------------------Declare function-----------------------------------------------------------
//Create basic window format
bool createWindow(HINSTANCE hInstance);
void cleanUpWindow(HINSTANCE hInstance);
bool windowIsRunning(HINSTANCE hInstance);
void render();

//Initialize (with sprtie)
void initializeGame();

//Create Input
void getInput();
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
	case WM_MOUSEMOVE:
		cursorPos.x = (short)LOWORD(lParam);
		cursorPos.y = (short)HIWORD(lParam);
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
	gameState = new MainMenu();
	GameStateManager::ChangeState(gameState);
}

//Get Input
void getInput() {
	
}


//Cleaning
void cleanUpAll(HINSTANCE hInstance) {
	//Clean Up 
	DirectInput::Release();
	Direct3DDeviceWrapper::CleanUp();
	cleanUpWindow(hInstance);
}

void cleanUpWindow(HINSTANCE hInstance) {
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

void render() {
	Direct3DDeviceWrapper::BeginRender();

	GameStateManager::Render();

	Direct3DDeviceWrapper::EndRender();
}


//------------------------------------------------------Main--------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	myTimer.init(90);
	//Create Window
	if (createWindow(hInstance))
	{
		//Create DirectX 
		if (Direct3DDeviceWrapper::CreateDevice(screenWidth, screenHeight, g_hWnd)) {
			//Create Dinput device
			
		}
	}
	else {
		MessageBox(g_hWnd, "Create Window Failed!!", NULL, MB_OK);
	}

	//Create Direct Input Device
	DirectInput::Initialize(g_hWnd);


	//Initialize and load the texture before enter the game
	initializeGame();

	while (windowIsRunning(hInstance))
	{
		GameStateManager::GetInput(DirectInput::getMouseInput());
		DirectInput::setMousePosition(cursorPos);

		//If need to change game state
		if (GameStateManager::GetIsChangeGameState()) {
			std::string gameStateToChange = GameStateManager::GetGameStateToChange();
			GameStateManager::ButtonClickEvent(gameStateToChange);

			//Go to change game state
			GameStateManager::OnClickButton(gameStateToChange);
			GameStateManager::SetIsChangeGameState(false);
		}

		GameStateManager::Update(myTimer.framesToUpdate());

		render();
	}

	//Clean Up Everything
	cleanUpAll(hInstance);
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------