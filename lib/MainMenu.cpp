#include "MainMenu.h"
#include <d3d9.h>
#include <vector>
#include <iostream>

MainMenu::MainMenu()
{
    bg = new GameObject(1, 1, 1, 600, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 0), 10);
    ground = new GameObject(1, 1, 1, 100, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 500), 10);
    golfBall = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 468), 10);
    golfTee = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 500), 10);
    golfClub = new GameObject(1, 1, 1, 64, 128, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(100, 372), 10);

    greyScreen = new GameObject(1, 1, 1, 600, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 0), 10);
    logoBack = new GameObject(1, 1, 1, 256, 512, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(244, 172), 10);
    playButton = new Button("GameLv1", 1, 1, 1, 64, 128, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(436, 400), 10);
    settingButton = new GameObject(1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(10, 526), 10);
    homeButton = new Button("GameOver",1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(926, 526), 10);

    audio = new AudioManager();
}

void MainMenu::Initialize()
{
    //initialize all the game objects
    bg->initialize("Image/bgPink.png");
    ground->initialize("Image/ground.png");
    golfBall->initialize("Image/ball.png");
    golfTee->initialize("Image/tee.png");
    golfTee->setColor(200, 27, 27);
    golfClub->initialize("Image/club.png");
    greyScreen->initialize("Image/greyScreen.png");
    logoBack->initialize("Image/logoBack.png");
    playButton->initialize("Image/playButton.png");
    settingButton->initialize("Image/settingButton.png");
    homeButton->initialize("Image/homeButton.png");

    gameObjects.push_back(bg);
    gameObjects.push_back(ground);
    gameObjects.push_back(golfBall);
    gameObjects.push_back(golfTee);
    gameObjects.push_back(golfClub);
    gameObjects.push_back(greyScreen);
    gameObjects.push_back(logoBack);
    gameObjects.push_back(playButton);
    gameObjects.push_back(settingButton);
    gameObjects.push_back(homeButton);


}

void MainMenu::Update(float deltaTime)
{
    for (GameObject* object : gameObjects) {
        //object->update(deltaTime);
    }
}

void MainMenu::Render()
{
    for (GameObject* object : gameObjects) {
        object->Render();
    }
}

void MainMenu::GetInput(bool input)
{
    for (GameObject* object : gameObjects) {
        object->getInput();
    }
}

void MainMenu::OnClickButton(const std::string& buttonName){

    //Chaneg Game State based on button name
    if (buttonName == "GameLv1") {
        GameStateManager::ChangeState(new GameLv1());
    }
    if (buttonName == "GameOver") {
        GameStateManager::ChangeState(new GameOver());
    }
}
/*
std::string MainMenu::GetName() const
{
    return "MainMenu";
}
*/

void MainMenu::Release()
{
    for (GameObject* object : gameObjects)
    {
        delete object;
    }
}