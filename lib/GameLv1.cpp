#include <d3d9.h>
#include "GameLv1.h"
//#include "Direct3DDeviceWrapper.cpp"
#include <iostream>

//This constructor method more effective
GameLv1::GameLv1() {
    bg = new GameObject(1, 1, 1, 600, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 0), 10);
    ground = new GameObject(1, 1, 1, 100, 1000, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(0, 500), 10);
    wood = new GameObject(1, 1, 1, 128, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(600, 404), 10);
    golfBall = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 468), 10);
    golfTee = new GameObject(1, 1, 1, 32, 32, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(164, 500), 10);
    golfClub = new PlayerControlledObject(1, 1, 1, 128, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(10, 372), 10);
    homeButton = new Button("MainMenu", 1, 1, 1, 64, 64, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(10, 10), 10);
    nextLvlButton = new Button("GameLv2", 1, 1, 1, 64, 256, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(372, 10), 10);
    portal = new GameObject(1, 8, 8, 64, 512, D3DXVECTOR2(1.0f, 1.0f), 0.0f, 0.0f, 0.0f, D3DXVECTOR2(800, 468), 10);

    physics.setAirResistance(0.99f);
    physics.setGravity(0.5f);
    physics.setWindForce(0.05f);

    audio = new AudioManager();
}

void GameLv1::Initialize() {
    audio->initializeAudio();
    audio->loadSounds();
    audio->playSoundTrack();

    bg->initialize("Image/bgPink.png");
    ground->initialize("Image/ground.png");
    wood->initialize("Image/wood.png");
    wood->setColor(207, 147, 87);
    golfBall->initialize("Image/ball.png");
    golfTee->initialize("Image/tee.png");
    golfTee->setColor(200, 27, 27);
    golfClub->initialize("Image/club.png");
    homeButton->initialize("Image/homeButton.png");
    nextLvlButton->initialize("Image/nextlvlButton.png");
    portal->initialize("Image/portalLong.png");


    // Add initialized GameObject objects to the container
    gameObjects.push_back(bg);
    gameObjects.push_back(ground);
    gameObjects.push_back(wood);
    gameObjects.push_back(golfBall);
    gameObjects.push_back(golfTee);
    gameObjects.push_back(golfClub);
    gameObjects.push_back(homeButton);
    gameObjects.push_back(nextLvlButton);
    gameObjects.push_back(portal);

}

void GameLv1::GetInput(bool input)
{
    for (GameObject* object : gameObjects) {
        object->getInput();

        //checks if objects is of type PlayerControlledObject
        if (PlayerControlledObject* poObject = dynamic_cast<PlayerControlledObject*>(object)) {
            poObject->getInput();
        }
    }
}


void GameLv1::Update(float deltaTime)
{
    for (int i = 0; i < deltaTime; i++) {
        frame++;
        golfBall->update();

    	physics.addAirResistance(golfBall);

        if (frame % 5 == 4) {
        	golfClub->setPrevPos(golfClub->getPosition());
        }

        //checks collision between golfclub and golfball
        if (physics.circleSquareCollision(golfClub, golfBall)
        	&& golfBall->getState() == PlayerControlledObject::Stationary) {
        			
        	golfBall->setState(PlayerControlledObject::Moving);
        
        	D3DXVECTOR2 totalForce = (golfClub->getPosition() - golfClub->getPrevPos()) * golfClub->getMass();
        	
        	golfBall->SetVelocity(totalForce / 2 / golfBall->getMass());
        
            audio->playGolfSwing();
        }

        //checks collision between wood and golfball
        if (physics.circleSquareCollision(wood, golfBall)) {

            if (golfBall->getPosition().x + golfBall->getSpriteWidth() > wood->getPosition().x) {
                D3DXVECTOR2 golfGetVel = golfBall->GetVelocity();
                golfGetVel.x *= -0.90;
                golfBall->SetVelocity(golfGetVel);
            }

            if (golfBall->getPosition().y + golfBall->getSpriteHeight() < wood->getPosition().y ) {
                D3DXVECTOR2 golfGetVel = golfBall->GetVelocity();
                golfGetVel.y *= -0.90;
                golfBall->SetVelocity(golfGetVel);
            }
            if (golfBall->GetVelocity() != D3DXVECTOR2(0,0))
                audio->playWoodHit();

        }

        //checks if ball touches portal
        if (physics.circleCollisionDetection(portal->getSpriteWidth() / 2, golfBall->getSpriteWidth() / 2,
            portal->getPosition(), golfBall->getPosition()) && state == GameLv1::inProgress) {
            state = GameLv1::win;
            gameObjects.erase(gameObjects.begin() + 3);
            audio->playWin();

        }

        //golfball window border collision
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

    for (GameObject* object : gameObjects) {
        object->update();
    }


}

void GameLv1::OnClickButton(const std::string& buttonName) {

    //Chaneg Game State based on button name
    if (buttonName == "GameLv2") {
        GameStateManager::ChangeState(new GameLv2());
    }

    if (buttonName == "MainMenu") {
        GameStateManager::ChangeState(new MainMenu());
    }
}

GameLv1::State GameLv1::getState() {
    return state;
}

void GameLv1::setState(State newState) {
    state = newState;
}


void GameLv1::Render()
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

void GameLv1::Release()
{
    for (GameObject* object : gameObjects)
    {
        delete object;
    }
    delete audio;
}

//Update() and Render() no need to write again since it is exactly same as Update() and Render() in GameState class


