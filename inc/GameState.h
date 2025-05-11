#pragma once
#include <string>

#include <vector>
#include "Direct3DDeviceWrapper.h"
#include "GameObject.h"
#include "Physics.h"
#include "AudioManager.h"
#define screenWidth 1000
#define screenHeight 600

class GameState {
public:

    virtual void Initialize() = 0;
    //Every gamestate class has same things to do in update() and render()
    virtual void OnClickButton(const std::string& buttonName);
    virtual void GetInput(bool input) = 0;
    //virtual std::string GetName() const;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Release() = 0;

protected:
    AudioManager* audio;
    Physics physics;
    int frame = 0;
    std::vector<GameObject*> gameObjects; //Every gamestate class has a vector to store game object
};


