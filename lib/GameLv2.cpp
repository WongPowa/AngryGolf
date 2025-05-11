#include <d3d9.h>
#include "GameLv2.h"
#include <vector>
#include <iostream>

GameLv2::GameLv2()
{
    bg = new GameObject(1, 1, 1, 600, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 0), 10);
    ground = new GameObject(1, 1, 1, 100, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 500), 10);
    golfBall = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 468), 10);
    golfTee = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 500), 10);
    golfClub = new PlayerControlledObject(1, 1, 1, 128, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(50, 372), 10);
    homeButton = new Button("MainMenu", 1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(10, 10), 10);
    nextLvlButton = new Button("GameLv3", 1, 1, 1, 64, 256, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(372, 10), 10);
    portal = new GameObject(1, 8, 8, 64, 512, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(800, 468), 10);

    physics.setAirResistance(0.99f);
    physics.setGravity(0.5f);
    physics.setWindForce(0.05f);

    audio = new AudioManager();
}

void GameLv2::Initialize()
{
    //initialize all the game objects
    audio->initializeAudio();
    audio->loadSounds();
    audio->playSoundTrack();

    bg->initialize("Image/bgPink.png");
    ground->initialize("Image/ground.png");
    golfBall->initialize("Image/ball.png");
    golfTee->initialize("Image/tee.png");
    golfTee->setColor(200, 27, 27);
    golfClub->initialize("Image/club.png");
    homeButton->initialize("Image/homeButton.png");
    nextLvlButton->initialize("Image/nextlvlButton.png");
    portal->initialize("Image/portalLong.png");

    gameObjects.push_back(bg);
    gameObjects.push_back(ground);
    gameObjects.push_back(golfBall);
    gameObjects.push_back(golfTee);
    gameObjects.push_back(golfClub);
    gameObjects.push_back(homeButton);
    gameObjects.push_back(nextLvlButton);
    gameObjects.push_back(portal);

}

void GameLv2::GetInput(bool input)
{
    for (GameObject* object : gameObjects) {
        object->getInput();

        if (PlayerControlledObject* poObject = dynamic_cast<PlayerControlledObject*>(object)) {
            poObject->getInput();
        }
    }
}

void GameLv2::OnClickButton(const std::string& buttonName) {

    //Chaneg Game State based on button name
    if (buttonName == "GameLv3") {
        GameStateManager::ChangeState(new GameLv3());
    }

    if (buttonName == "MainMenu") {
        GameStateManager::ChangeState(new MainMenu());
    }
}

void GameLv2::Update(float deltaTime)
{
    for (int i = 0; i < deltaTime; i++) {
        frame++;
        golfBall->update();

        physics.addAirResistance(golfBall);
        
        //add wind
        if (golfBall->getState() == PlayerControlledObject::Moving)
        	physics.addWindForce(golfBall);

        if (frame % 5 == 4) {
            golfClub->setPrevPos(golfClub->getPosition());
        }

        //checks collision for golfClub and golfBall
        if (physics.circleSquareCollision(golfClub, golfBall)
            && golfBall->getState() == PlayerControlledObject::Stationary) {

            golfBall->setState(PlayerControlledObject::Moving);

            D3DXVECTOR2 totalForce = (golfClub->getPosition() - golfClub->getPrevPos()) * golfClub->getMass();

            golfBall->SetVelocity(totalForce / 2 / golfBall->getMass());

            audio->playGolfSwing();

        }

        //checks if golfball collides with portal
        if (physics.circleCollisionDetection(portal->getSpriteWidth() / 2, golfBall->getSpriteWidth() / 2,
            portal->getPosition(), golfBall->getPosition()) && state == GameLv2::inProgress) {
            gameObjects.erase(gameObjects.begin() + 2);
            state = GameLv2::win;
            audio->playWin();

        }

        //boundary collision for golfball
        if (golfBall->getPosition().y < 0 || golfBall->getPosition().y > screenHeight - golfBall->getSpriteHeight() - ground->getSpriteHeight() + 20) {
            D3DXVECTOR2 golfGetVel = golfBall->GetVelocity();
            golfGetVel.y *= -0.90;
            golfBall->SetVelocity(golfGetVel);
        }
        else {
            if (golfBall->getState() == PlayerControlledObject::Moving) {
                physics.addGravity(golfBall);
            }
        }

        if (golfBall->getPosition().x < 0 || golfBall->getPosition().x > screenWidth - golfBall->getSpriteWidth()) {
            D3DXVECTOR2 golfGetVel = golfBall->GetVelocity();
            golfGetVel.x *= -0.90;
            golfBall->SetVelocity(golfGetVel);
        }
        audio->updateSound();
    }
}

void GameLv2::Render()
{

    RECT portalRect;
    portalRect.left = ((frame - 1) % portal->getSpriteMaxFrame()) * portal->getSpriteWidth();
    portalRect.top = 0;
    portalRect.right = portalRect.left + portal->getSpriteWidth();
    portalRect.bottom = portal->getSpriteHeight();
    portal->setRect(portalRect);
    for (GameObject* object : gameObjects) {
        object->Render();
    }
}

void GameLv2::Release()
{
    for (GameObject* object : gameObjects)
    {
        delete object;
    }
    delete audio;
}
