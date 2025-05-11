#pragma once
#include "GameObject.h"

class PlayerControlledObject : public GameObject {
public:
    PlayerControlledObject(int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
        int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
        float newScalingRotationFactor, float newRotation, float newRotationSpeed,
        D3DXVECTOR2 newPosition, float newMass);

    void getInput() override;
    void setPoint(POINT newCursorPos);
    void setPrevPos(D3DXVECTOR2 newPrevPos);
    D3DXVECTOR2 getPrevPos();
    //update
    //render

private:
    POINT cursorPos;
    D3DXVECTOR2 prevPos;
    //HWND g_hWnd;
    //State state;
};

