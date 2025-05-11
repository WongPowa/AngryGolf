#pragma once 
#include <vector>
#include <d3d9.h>
#include "Direct3DDeviceWrapper.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "GameState.h"
#include "GameOver.h"
#include "Button.h"

class MainMenu : public GameState
{
public:
    MainMenu();

    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Release();
    void GetInput(bool input) override;
    //std::string GetName() const override;
    void OnClickButton(const std::string& buttonName) override;

private:
    GameObject* bg;
    GameObject* ground;
    GameObject* golfBall;
    GameObject* golfTee;
    GameObject* golfClub;

    GameObject* greyScreen;
    GameObject* logoBack;
    Button* playButton;
    GameObject* settingButton;
    Button* homeButton;
};

