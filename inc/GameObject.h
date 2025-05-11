#pragma once
#include <d3dx9.h>
#include "Direct3DDeviceWrapper.h"
#include "DirectInput.h"

class GameObject
{
public:
    GameObject();
    GameObject(int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
        int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling, float newScalingRotationFactor,
        float newRotation, float rotaionSpeed, D3DXVECTOR2 newPosition, float newMass);
    ~GameObject();

    enum State {
        Moving,
        Stationary
    };

    void setState(State newState);
    State getState() const;
    /*

    void ApplyForce(D3DXVECTOR2 force);

    void SetTextureSize(int texturewidth, int textureheight);

    void SetSpriteSheetInfo(int rows, int cols, int maxFrames, int width, int height);

    void SetCurrentFrame(int frame);
    int GetCurrentFrame() const;

    void SetSize(D3DXVECTOR2 newSize);
    D3DXVECTOR2 GetSize() const;


    */

    //---physics---
    void setMass(float newMass);
    float getMass() const;

    void setPosition(D3DXVECTOR2 newPosition);
    D3DXVECTOR2 getPosition() const;

    void SetVelocity(D3DXVECTOR2 newVelocity);
    D3DXVECTOR2 GetVelocity() const;

    void addVelocity(D3DXVECTOR2 newVelocity);

    void SetAcceleration(D3DXVECTOR2 newAcceleration);
    D3DXVECTOR2 GetAcceleration() const;

    void setForce(D3DXVECTOR2 newForce);
    D3DXVECTOR2 getForce() const;

    void addForce(D3DXVECTOR2 newForce);

    void setCollisionBox(RECT newCollisionBox);
    RECT getCollisionBox();

    //---sprite properties---
    void setTextureWidth(int newTextureWidth);
    int getTextureWidth();

    void setTextureHeight(int newTextureHeight);
    int getTextureHeight();

    void setSpriteRow(int newSpriteRow);
    int getSpriteRow();

    void setSpriteCol(int newSpriteCol);
    int getSpriteCol();

    void setSpriteWidth(int newSpriteWidth);
    int getSpriteWidth();

    void setSpriteHeight(int newSpriteHeight);
    int getSpriteHeight();

    void setSpriteMaxFrame(int newSpriteMaxFrame);
    int getSpriteMaxFrame();

    void setRect(RECT& newRect);
    RECT getRect();

    //---colors---
    void setColor(int newRed, int newGreen, int newBlue);

    void setRed(int newRed);
    int getRed();

    void setGreen(int newGreen);
    int getGreen();

    void setBlue(int newBlue);
    int getBlue();

    //---matrix---
    void SetTexture(LPDIRECT3DTEXTURE9 newTexture);
    LPDIRECT3DTEXTURE9& GetTexture();

    void setMatrix(D3DXMATRIX newMatrix);
    D3DXMATRIX getMatrix() const;

    void setScaling(D3DXVECTOR2 newScaling);
    D3DXVECTOR2 getScaling() const;

    void setScalingCenterPoint(D3DXVECTOR2 newScalingCenterPoint);
    D3DXVECTOR2 getScalingCenterPoint() const;

    void setScalingRotationFactor(float factor);
    float getScalingRotationFactor() const;

    void setRotation(float newRotation);
    float getRotation() const;

    void setRotationCenterPoint(D3DXVECTOR2 newRotationCenterPoint);
    D3DXVECTOR2 getRotationCenterPoint() const;

    void setRotationSpeed(float speed);
    float getRotationSpeed() const;

    //scaling, center point whatever...

    void update();
    virtual void getInput() {};
    //virtual void update();
    void Render();
    void initialize(LPCSTR imgPath);


protected:
    //---physics---
    D3DXVECTOR2 position;
    D3DXVECTOR2 force;
    D3DXVECTOR2 velocity;
    D3DXVECTOR2 acceleration;
    int currentFrame;
    D3DXVECTOR2 size;
    float mass;
    RECT collisionBox;

    //---sprite properties---
    int textureWidth;
    int textureHeight;
    int spriteRow;
    int spriteCol;
    int spriteMaxFrame;
    int spriteWidth;
    int spriteHeight;
    RECT rect;

    //---colors---
    int red = 255;
    int green = 255;
    int blue = 255;

    //---matrix---
    D3DXMATRIX matrix;
    D3DXVECTOR2 scaling;
    D3DXVECTOR2 scalingCenterPoint;
    float scalingRotationFactor;
    float rotation;
    D3DXVECTOR2 rotationCenterPoint;
    float rotationSpeed;

    LPDIRECT3DTEXTURE9 texture;

    State state;
};

