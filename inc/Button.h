#pragma once
#include <d3dx9.h>
#include <string>
#include "DirectInput.h"
#include "GameObject.h"


class Button : public GameObject {
public:
    Button();
    Button(const std::string& name, int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
        int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
        float newScalingRotationFactor, float newRotation, float rotationSpeed,
        D3DXVECTOR2 newPosition, float newMass);
    ~Button();

    void getInput() override;

private:
    std::string buttonName;

};
