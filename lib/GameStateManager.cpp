#include "GameStateManager.h"

std::vector<GameState*> GameStateManager::gameStates;
GameState* GameStateManager::currentState = nullptr;
std::string GameStateManager::gameStateToChange;
bool GameStateManager::isChangeGameState = false;

void GameStateManager::ChangeState(GameState* newState) {
    // Change to a new game state
    if (currentState != nullptr) {
        currentState->Release();
        delete currentState; // Release the old game state since there have destructor
        gameStates.pop_back(); // Remove the old state from the vector
    }
    gameStates.push_back(newState); // Add the new state to the vector
    currentState = newState; // Set the new game state
    currentState->Initialize(); // Initialize the new state
}

//Set name to attribute
void GameStateManager::ButtonClickEvent(const std::string& buttonName)
{
    gameStateToChange = buttonName;
    isChangeGameState = true;
}

//Set name to attribute
// 
//Change state
void GameStateManager::OnClickButton(const std::string& buttonName)
{

    currentState->OnClickButton(buttonName);
}

void GameStateManager::Update(float deltaTime) {
    // Update the current game state
    if (currentState != nullptr) {
        currentState->Update(deltaTime);
    }
}

void GameStateManager::GetInput(bool input) {
    if (currentState != nullptr) {
        currentState->GetInput(input);
    }
}


bool GameStateManager::GetIsChangeGameState()
{
    return isChangeGameState;
}

void GameStateManager::SetIsChangeGameState(bool value)
{
    isChangeGameState = value;
}

std::string GameStateManager::GetGameStateToChange()
{
    return gameStateToChange;
}

void GameStateManager::Render() {
    // Render the current game state
    if (currentState != nullptr) {
        currentState->Render();
    }
}