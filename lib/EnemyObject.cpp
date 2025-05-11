#include "EnemyObject.h"

EnemyObject::EnemyObject(int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
    int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
    float newScalingRotationFactor, float newRotation, float newRotationSpeed,
    D3DXVECTOR2 newPosition, float newMass, float newMovementSpeed) : GameObject(newSpriteRow, newSpriteCol, newSpriteMaxFrame,
        newTextureHeight, newTextureWidth, newScaling, newScalingRotationFactor,
        newRotation, newRotationSpeed, newPosition, newMass)
{
    movementSpeed = newMovementSpeed;
}

void EnemyObject::chase(GameObject& gameObj, float deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        D3DXVECTOR2 distanceVec = gameObj.getPosition() - position;


        D3DXVec2Normalize(&chaseVec, &distanceVec);

        velocity = movementSpeed * chaseVec;
    }

}
