#pragma once
#include "GameObject.h" 
#include <vector>
#include <d3d9.h>
#include "PlayerControlledObject.h"
#include "EnemyObject.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Button.h"

class GameLv3 : public GameState {
public:
    GameLv3();

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
    GameObject* bg;
    GameObject* ground;
    GameObject* wood;
    EnemyObject* ghost;
    GameObject* golfBall;
    GameObject* golfTee;
    PlayerControlledObject* golfClub;
    Button* homeButton;
    Button* nextLvlButton;
    GameObject* portal;
    GameObject* evilPortal;

    State state = inProgress;
};


