#include "GameObject.h"
#include <d3dx9.h>
#include <iostream>

using namespace std;

#define screenWidth 1440
#define screenHeight 900

GameObject::GameObject() {
    texture = nullptr;
};

GameObject::GameObject(int newSpriteRow, int newSpriteCol, int newSpriteMaxFrame,
    int newTextureHeight, int newTextureWidth, D3DXVECTOR2 newScaling,
    float newScalingRotationFactor, float newRotation, float newRotationSpeed,
    D3DXVECTOR2 newPosition, float newMass) {

    //physics
    position = newPosition;
    mass = newMass;
    force = D3DXVECTOR2(0.0f, 0.0f);
    velocity = D3DXVECTOR2(0.0f, 0.0f);
    acceleration = D3DXVECTOR2(0.0f, 0.0f);

    collisionBox = RECT();

    // Set null to texture
    spriteRow = newSpriteRow;
    spriteCol = newSpriteCol;
    spriteMaxFrame = newSpriteMaxFrame;
    textureWidth = newTextureWidth; // You can modify the initial sprite width
    textureHeight = newTextureHeight; // You can modify the initial sprite height
    spriteWidth = textureWidth / spriteCol;
    spriteHeight = textureHeight / spriteRow;

    rect = RECT();

    //Matrix
    scaling = newScaling;
    scalingRotationFactor = newScalingRotationFactor;
    rotation = newRotation;
    rotationSpeed = newRotationSpeed;
    scalingCenterPoint = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
    rotationCenterPoint = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

    texture = nullptr;

    state = Stationary;
}

GameObject::~GameObject() {
    // Relase texture
    if (texture != nullptr) {
        texture->Release();
        texture = nullptr;
    }
}
/*

void GameObject::setSize(D3DXVECTOR2 newSize) {
    size = newSize;
}

D3DXVECTOR2 GameObject::getSize() const {
    return size;
}
*/

//---physics---
void GameObject::setPosition(D3DXVECTOR2 newPosition) {
    position = newPosition;
}

void GameObject::setMass(float newMass) {
    mass = newMass;
}

float GameObject::getMass() const {
    return mass;
}

void GameObject::SetVelocity(D3DXVECTOR2 newVelocity) {
    velocity = newVelocity;
}

D3DXVECTOR2 GameObject::GetVelocity() const {
    return velocity;
}

void GameObject::addVelocity(D3DXVECTOR2 newVelocity) {
    velocity += newVelocity;
}

void GameObject::SetAcceleration(D3DXVECTOR2 newAcceleration) {
    acceleration = newAcceleration;
}

D3DXVECTOR2 GameObject::GetAcceleration() const {
    return acceleration;
}

D3DXVECTOR2 GameObject::getPosition() const {
    return position;
}

void GameObject::setForce(D3DXVECTOR2 newForce) {
    force = newForce;
}

D3DXVECTOR2 GameObject::getForce() const {
    return force;
}

void GameObject::addForce(D3DXVECTOR2 newForce) {
    force += newForce;
}

void GameObject::setCollisionBox(RECT newCollisionBox) {
    collisionBox = newCollisionBox;
}
RECT GameObject::getCollisionBox() {
    return collisionBox;
}

//---sprite properties---
void GameObject::setTextureWidth(int newTextureWidth) {
    textureWidth = newTextureWidth;
}

int GameObject::getTextureWidth() {
    return textureWidth;
}

void GameObject::setTextureHeight(int newTextureHeight) {
    textureHeight = newTextureHeight;
}

int GameObject::getTextureHeight() {
    return textureHeight;
}

void GameObject::setSpriteRow(int newSpriteRow) {
    spriteRow = newSpriteRow;
}

int GameObject::getSpriteRow() {
    return spriteRow;
}

void GameObject::setSpriteCol(int newSpriteCol) {
    spriteCol = newSpriteCol;
}

int GameObject::getSpriteCol() {
    return spriteCol;
}

void  GameObject::setSpriteWidth(int newSpriteWidth) {
    spriteWidth = newSpriteWidth;
}

int GameObject::getSpriteWidth() {
    return spriteWidth;
}

void GameObject::setSpriteHeight(int newSpriteHeight) {
    spriteHeight = newSpriteHeight;
}

int GameObject::getSpriteHeight() {
    return spriteHeight;
}

void GameObject::setSpriteMaxFrame(int newSpriteMaxFrame) {
    spriteMaxFrame = newSpriteMaxFrame;
}

int GameObject::getSpriteMaxFrame() {
    return spriteMaxFrame;
}

void GameObject::setRect(RECT& newRect) {
    rect = newRect;
}

RECT GameObject::getRect() {
    return rect;
}

//---sprite color---
void GameObject::setColor(int newRed, int newGreen, int newBlue) {
    red = newRed;
    green = newGreen;
    blue = newBlue;
}

void GameObject::setRed(int newRed) {
    red = newRed;
}
int GameObject::getRed() {
    return red;
}

void GameObject::setGreen(int newGreen) {
    green = newGreen;
}
int GameObject::getGreen() {
    return green;
}

void GameObject::setBlue(int newBlue) {
    blue = newBlue;
}
int GameObject::getBlue() {
    return blue;
}

//---matrix---
void GameObject::SetTexture(LPDIRECT3DTEXTURE9 newTexture) {
    texture = newTexture;
}

//No need to get Texture?
LPDIRECT3DTEXTURE9& GameObject::GetTexture() {
    return texture;
}

void GameObject::setMatrix(D3DXMATRIX newMatrix) {
    matrix = newMatrix;
}

D3DXMATRIX GameObject::getMatrix() const {
    return matrix;
}

void GameObject::setScaling(D3DXVECTOR2 newScaling) {
    scaling = newScaling;
}

D3DXVECTOR2 GameObject::getScaling() const {
    return scaling;
}

void GameObject::setScalingCenterPoint(D3DXVECTOR2 newScalingCenterPoint) {
    scalingCenterPoint = newScalingCenterPoint;
}

D3DXVECTOR2 GameObject::getScalingCenterPoint() const {
    return scalingCenterPoint;
}

void GameObject::setScalingRotationFactor(float factor) {
    scalingRotationFactor = factor;
}

float GameObject::getScalingRotationFactor() const {
    return scalingRotationFactor;
}

void GameObject::setRotation(float newRotation) {
    rotation = newRotation;
}

float GameObject::getRotation() const {
    return rotation;
}

void GameObject::setRotationCenterPoint(D3DXVECTOR2 newRotationCenterPoint) {
    rotationCenterPoint = newRotationCenterPoint;
}

D3DXVECTOR2 GameObject::getRotationCenterPoint() const {
    return rotationCenterPoint;
}

void GameObject::setRotationSpeed(float newRotationSpeed) {
    rotationSpeed = newRotationSpeed;
}

float GameObject::getRotationSpeed() const {
    return rotationSpeed;
}

void GameObject::setState(State newState) {
    state = newState;
}

GameObject::State GameObject::getState() const {
    return state;
}

//Input
void GameObject::update()
{
    acceleration = force / mass;
    velocity += acceleration;
    position += velocity;

    collisionBox.top = position.y;
    collisionBox.bottom = collisionBox.top + spriteHeight;
    collisionBox.left = position.x;
    collisionBox.right = collisionBox.left + spriteWidth;

    /*1. Force
        2. Acceleration
        3. Velocity
        4. Position*/
}

void GameObject::Render() {
    // Render using the passed-in sprite object
    D3DXMatrixTransformation2D(&matrix, &scalingCenterPoint, scalingRotationFactor,
        &scaling, &rotationCenterPoint, rotation, &position);
    Direct3DDeviceWrapper::setSpriteBrushTransform(matrix);
    if (texture != nullptr) {
        Direct3DDeviceWrapper::DrawSprite(texture, rect, D3DCOLOR_XRGB(red, green, blue));
    }
}

void GameObject::initialize(LPCSTR imgPath) {
    Direct3DDeviceWrapper::LoadTextureFromFile(imgPath, texture);
}


