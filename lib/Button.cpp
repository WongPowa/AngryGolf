#include "Button.h"
#include "GameStateManager.h"
#include <iostream>

using namespace std;

Button::Button() : GameObject() {
    // Initialize specific button properties here
    // For example, texture, pressed state, etc.
    texture = nullptr;

}

Button::Button(const std::string& name, int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
    int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
    float newScalingRotationFactor, float newRotation, float rotationSpeed,
    D3DXVECTOR2 newPosition, float newMass) : GameObject(newSpriteRow, newSpriteCol, newSpriteMaxFrame,
        newTextureHeight, newTextureWidth, newScaling, newScalingRotationFactor,
        newRotation, rotationSpeed, newPosition, newMass), buttonName(name) {
}


Button::~Button() {
    if (texture != nullptr) {
        texture->Release();
        texture = nullptr;
    }
}
void Button::getInput() {
    //Check if mouse click
    int mouseX = DirectInput::getMousePositionX();
    int mouseY = DirectInput::getMousePositionY();


    if (mouseX >= position.x &&
        mouseX <= position.x + spriteWidth &&
        mouseY >= position.y &&
        mouseY <= position.y + spriteHeight) {

        red = 211, blue = 211, green = 211;

        if (DirectInput::getIsMouseButtonDown()) {
            GameStateManager::ButtonClickEvent(buttonName);
        }

    }
    else {
        red = 255, blue = 255, green = 255;
    }

 

}

