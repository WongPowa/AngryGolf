#include <d3d9.h>
#include "GameLv3.h"
#include <vector>
#include <iostream>

GameLv3::GameLv3()
{
    bg = new GameObject(1, 1, 1, 600, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 0), 10);
    ground = new GameObject(1, 1, 1, 100, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 500), 10);
    wood = new GameObject(1, 1, 1, 128, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(660, 404), 10);
    ghost = new EnemyObject(1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(543, 445), 50, 2);
    golfBall = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 468), 10);
    golfTee = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 500), 10);
    golfClub = new PlayerControlledObject(1, 1, 1, 128, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(50, 372), 10);
    homeButton = new Button("MainMenu", 1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(10, 10), 10);
    nextLvlButton = new Button("MainMenu", 1, 1, 1, 64, 256, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(372, 10), 10);
    portal = new GameObject(1, 8, 8, 64, 512, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(800, 468), 10);
    evilPortal = new GameObject(1, 8, 8, 64, 512, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(900, 468), 10);

    physics.setAirResistance(0.99f);
    physics.setGravity(0.5f);
    physics.setWindForce(0.05f);

    audio = new AudioManager();
}

void GameLv3::Initialize()
{
    //initialize all the game objects
    audio->initializeAudio();
    audio->loadSounds();
    audio->playSoundTrack();

    bg->initialize("Image/bgPink.png");
    ground->initialize("Image/ground.png");
    wood->initialize("Image/wood.png");
    wood->setColor(207, 147, 87);
    ghost->initialize("Image/ghost.png");
    ghost->setColor(122, 190, 210);
    golfBall->initialize("Image/ball.png");
    golfTee->initialize("Image/tee.png");
    golfTee->setColor(200, 27, 27);
    golfClub->initialize("Image/club.png");
    homeButton->initialize("Image/homeButton.png");
    nextLvlButton->initialize("Image/nextlvlButton.png");
    portal->initialize("Image/portalLong.png");
    evilPortal->initialize("Image/portalLong.png");
    evilPortal->setColor(255, 50, 50);

    gameObjects.push_back(bg);
    gameObjects.push_back(ground);
    gameObjects.push_back(wood);
    gameObjects.push_back(ghost);
    gameObjects.push_back(golfBall);
    gameObjects.push_back(golfTee);
    gameObjects.push_back(golfClub);
    gameObjects.push_back(homeButton);
    gameObjects.push_back(nextLvlButton);
    gameObjects.push_back(portal);
    gameObjects.push_back(evilPortal);

}

void GameLv3::GetInput(bool input)
{
    for (GameObject* object : gameObjects) {
        object->getInput();

        if (PlayerControlledObject* poObject = dynamic_cast<PlayerControlledObject*>(object)) {
            poObject->getInput();
        }
    }
}

void GameLv3::OnClickButton(const std::string& buttonName) {

    //Chaneg Game State based on button name
    if (buttonName == "MainMenu") {
        GameStateManager::ChangeState(new MainMenu());
    }
}

void GameLv3::Update(float deltaTime)
{
    for (int i = 0; i < deltaTime; i++) {
        frame++;
        golfBall->update();
        ghost->update();

        physics.addAirResistance(golfBall);

        if (frame % 5 == 4) {
            golfClub->setPrevPos(golfClub->getPosition());
        }

        if (physics.circleSquareCollision(golfClub, golfBall)
            && golfBall->getState() == PlayerControlledObject::Stationary) {

            golfBall->setState(PlayerControlledObject::Moving);

            D3DXVECTOR2 totalForce = (golfClub->getPosition() - golfClub->getPrevPos()) * golfClub->getMass();

            golfBall->SetVelocity(totalForce / 2 / golfBall->getMass());

            audio->playGolfSwing();

        }

        if (physics.circleSquareCollision(wood, golfBall)) {

            if (golfBall->getPosition().x + golfBall->getSpriteWidth() > wood->getPosition().x) {
                D3DXVECTOR2 golfGetVel = golfBall->GetVelocity();
                golfGetVel.x *= -0.90;
                golfBall->SetVelocity(golfGetVel);
            }

            if (golfBall->getPosition().y + golfBall->getSpriteHeight() > wood->getPosition().y) {
                D3DXVECTOR2 golfGetVel = golfBall->GetVelocity();
                golfGetVel.y *= -0.90;
                golfBall->SetVelocity(golfGetVel);
            }
            if (golfBall->GetVelocity() != D3DXVECTOR2(0, 0))
                audio->playWoodHit();
        }

        if (physics.circleSquareCollision(wood, ghost)) {

            if (ghost->getPosition().x + ghost->getSpriteWidth() > wood->getPosition().x) {
                D3DXVECTOR2 golfGetVel = ghost->GetVelocity();
                golfGetVel.x *= -0.90;
                ghost->SetVelocity(golfGetVel);
            }

            if (ghost->getPosition().y + ghost->getSpriteHeight() > wood->getPosition().y) {
                D3DXVECTOR2 golfGetVel = ghost->GetVelocity();
                golfGetVel.y *= -0.90;
                ghost->SetVelocity(golfGetVel);
            }
            if (ghost->GetVelocity() != D3DXVECTOR2(0, 0))
                audio->playWoodHit();
        }

        if (physics.circleCollisionDetection(golfBall->getSpriteWidth() / 2, ghost->getSpriteWidth() / 2, golfBall->getPosition(), ghost->getPosition())) {
            D3DXVECTOR2 golfVel = golfBall->GetVelocity();

            D3DXVECTOR2 colNormal = golfBall->getPosition() - ghost->getPosition();
            D3DXVec2Normalize(&colNormal, &colNormal);
            D3DXVECTOR2 velNormal = colNormal * D3DXVec2Dot(&golfVel, &colNormal);
            D3DXVECTOR2 velTangent = golfVel - velNormal;
            D3DXVECTOR2 bounceVector = velTangent - velNormal;

            D3DXVECTOR2 totalForce = golfBall->GetVelocity() * golfBall->getMass();
            ghost->SetVelocity(golfBall->GetVelocity() + totalForce / 2 / ghost->getMass());

            golfBall->SetVelocity(bounceVector);
        }

        if (ghost->getPosition().y < 0 || ghost->getPosition().y > screenHeight - ghost->getSpriteHeight() - ground->getSpriteHeight() + 20) {
            D3DXVECTOR2 golfGetVel = ghost->GetVelocity();
            golfGetVel.y *= -0.90;
            ghost->SetVelocity(golfGetVel);
        }

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

        if (ghost->getPosition().x < 0 || ghost->getPosition().x > screenWidth - ghost->getSpriteWidth()) {
            D3DXVECTOR2 golfGetVel = ghost->GetVelocity();
            golfGetVel.x *= -0.90;
            ghost->SetVelocity(golfGetVel);
        }

        if (physics.circleCollisionDetection(portal->getSpriteWidth() / 2, golfBall->getSpriteWidth() / 2,
            portal->getPosition(), golfBall->getPosition()) && state == GameLv3::inProgress) {
            gameObjects.erase(gameObjects.begin() + 4);
            state = GameLv3::win;
            audio->playWin();
        }

        if (physics.circleCollisionDetection(evilPortal->getSpriteWidth() / 2, golfBall->getSpriteWidth() / 2,
            portal->getPosition(), golfBall->getPosition()) && state == GameLv3::inProgress) {
            gameObjects.erase(gameObjects.begin() + 4);
            state = GameLv3::lose;
            audio->playWin();

        }

        audio->updateSound();
    }
}

void GameLv3::Render()
{
    RECT portalRect;
    portalRect.left = ((frame - 1) % portal->getSpriteMaxFrame()) * portal->getSpriteWidth();
    portalRect.top = 0;
    portalRect.right = portalRect.left + portal->getSpriteWidth();
    portalRect.bottom = portal->getSpriteHeight();
    portal->setRect(portalRect);
    evilPortal->setRect(portalRect);

    for (GameObject* object : gameObjects) {
        object->Render();
    }
}

void GameLv3::Release()
{
    for (GameObject* object : gameObjects)
    {
        delete object;
    }
    delete audio;
}
