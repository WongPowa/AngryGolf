#include "GameOver.h"
#include <d3d9.h>
#include <vector>
#include <iostream>

GameOver::GameOver()
{
    blackScreen = new GameObject(1, 1, 1, 1024, 1024, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 0), 10);
    homeWrittenButton = new Button("MainMenu", 1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(436, 400), 10);

    audio = new AudioManager();
}

void GameOver::Initialize()
{
    //initialize all the game objects
    audio->initializeAudio();
    audio->loadSounds();
    audio->playLose();

    blackScreen->initialize("Image/blackScreen.png");
    homeWrittenButton->initialize("Image/homeWrittenButton.png");

    gameObjects.push_back(blackScreen);
    gameObjects.push_back(homeWrittenButton);

}

void GameOver::Update(float deltaTime)
{
    for (int i = 0; i < deltaTime; i++) {
        audio->updateSound();
    }
}

void GameOver::Render()
{
    for (GameObject* object : gameObjects) {
        object->Render();
    }
}

void GameOver::GetInput(bool input)
{
    for (GameObject* object : gameObjects) {
        object->getInput();
    }
}

void GameOver::OnClickButton(const std::string& buttonName) {

    //Chaneg Game State based on button name
    if (buttonName == "MainMenu") {
        GameStateManager::ChangeState(new MainMenu());
    }
}

void GameOver::Release()
{
    for (GameObject* object : gameObjects)
    {
        delete object;
    }
    delete audio;
}
