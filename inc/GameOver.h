#pragma once 
#include <vector>
#include <d3d9.h>
#include "Direct3DDeviceWrapper.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "GameState.h"
#include "Button.h"

class GameOver : public GameState
{
public:
    GameOver();

    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Release();
    void GetInput(bool input) override;
    //std::string GetName() const override;
    void OnClickButton(const std::string& buttonName) override;

private:
    GameObject* blackScreen;
    Button* homeWrittenButton;
};

