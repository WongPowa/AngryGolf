#pragma once
#include "GameObject.h" 
#include <vector>
#include <d3d9.h>
#include "PlayerControlledObject.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Button.h"
#include "GameLv3.h"

class GameLv2 : public GameState {
public:
    GameLv2();

    void Initialize() override;

    void Update(float deltaTime) override;
    void Render() override;
    void GetInput(bool input) override;
    void Release();
    void OnClickButton(const std::string& buttonName) override;

    enum State {
        win,
        lose,
        inProgress,
        pause
    };

    State getState();
    void setState(State newState);

private:
    GameObject* bg = nullptr;
    GameObject* ground = nullptr;
    GameObject* golfBall = nullptr;
    GameObject* golfTee = nullptr;
    PlayerControlledObject* golfClub = nullptr;
    Button* homeButton = nullptr;
    Button* nextLvlButton = nullptr;
    GameObject* portal = nullptr;

    State state = inProgress;
};


