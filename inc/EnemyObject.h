#pragma once
#include "GameObject.h"

class EnemyObject : public GameObject
{
public:
	EnemyObject(int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
        int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
        float newScalingRotationFactor, float newRotation, float newRotationSpeed,
        D3DXVECTOR2 newPosition, float newMass, float newSpeed);

    void chase(GameObject &gameObj, float deltaTime);

private:
    D3DXVECTOR2 chaseVec;
    float movementSpeed;
};

