#pragma once
#include "GameObject.h" 
#include <vector>
#include <d3d9.h>
#include "PlayerControlledObject.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GameLv2.h"
#include "Button.h"

class GameLv1 : public GameState {
public:
    GameLv1();

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

    //std::string GetName() const override;

    State getState();
    void setState(State newState);

private:
    GameObject* bg = nullptr;
    GameObject* ground = nullptr;
    GameObject* wood = nullptr;
    GameObject* golfBall = nullptr;
    GameObject* golfTee = nullptr;
    PlayerControlledObject* golfClub = nullptr;
    GameObject* homeButton = nullptr;
    Button* nextLvlButton = nullptr;
    GameObject* portal = nullptr;

    State state = inProgress;
};


