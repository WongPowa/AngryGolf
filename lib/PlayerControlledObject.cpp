#include "PlayerControlledObject.h"
#include "common.h"

PlayerControlledObject::PlayerControlledObject(int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
    int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
    float newScalingRotationFactor, float newRotation, float newRotationSpeed,
    D3DXVECTOR2 newPosition, float newMass) : GameObject(newSpriteRow, newSpriteCol, newSpriteMaxFrame,
        newTextureHeight, newTextureWidth, newScaling, newScalingRotationFactor,
        newRotation, newRotationSpeed, newPosition, newMass) {

}

void PlayerControlledObject::setPrevPos(D3DXVECTOR2 newPrevPos) {
    prevPos = newPrevPos;
}

D3DXVECTOR2 PlayerControlledObject::getPrevPos() {
    return prevPos;
}

void PlayerControlledObject::getInput() {
    GetCursorPos(&cursorPos);
    ScreenToClient(g_hWnd, &cursorPos);
    D3DXVECTOR2 newPosition = D3DXVECTOR2(cursorPos.x, cursorPos.y);
        
    position = newPosition;
}

void PlayerControlledObject::setPoint(POINT newCursorPos) {
    cursorPos = newCursorPos;
}
