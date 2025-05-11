#pragma once
#include <vector>
#include <string>
#include "GameState.h"
#include "MainMenu.h" 
#include "GameLv1.h"  
//#include "GameLv2.h"  
//#include "GameLv3.h"  
//#include "GameOver.h"


class GameStateManager {
public:
    static void ChangeState(GameState* newState);
    static void ButtonClickEvent(const std::string& buttonName);
    static void OnClickButton(const std::string& buttonName);
    static void Update(float deltaTime);
    static void GetInput(bool input);
    static bool GetIsChangeGameState();
    static void SetIsChangeGameState(bool value);
    static std::string GetGameStateToChange();
    static void Render();

private:
    static std::vector<GameState*> gameStates; // Store gamestate to modify
    static GameState* currentState; // Current game state
    static std::string gameStateToChange;
    static bool isChangeGameState;
};