#include "GameState.h"

/*
std::string GameState::GetName() const
{
    return std::string();
}
*/

void GameState::OnClickButton(const std::string& buttonName){

}

void GameState::Update(float deltaTime) {
    for (GameObject* object : gameObjects) {
        object->update();
    }
}

void GameState::Render() {
    for (GameObject* object : gameObjects) {
        object->Render();
    }
}
