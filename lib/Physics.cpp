#include "Physics.h"
#include "cstdlib"
#include <iostream>
using namespace std;

Physics::Physics(float newAirResistance, float newGravity, float newWindForce) {
	airResistance = newAirResistance;
	gravity = newGravity;
	windForce = newWindForce;
}

Physics::Physics() {}

bool Physics::squareCollisionDetection(GameObject& obj1, GameObject& obj2) {
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = obj1.getPosition().x;
	left2 = obj2.getPosition().x;
	right1 = left1 + obj1.getSpriteWidth();
	right2 = left2 + obj2.getSpriteWidth();
	top1 = obj1.getPosition().y;
	top2 = obj2.getPosition().y;
	bottom1 = top1 + obj1.getSpriteHeight();
	bottom2 = top2 + obj2.getSpriteHeight();

	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;
	if (right1 < left2) return false;
	if (left1 > right2) return false;

	return true;
}

bool Physics::circleCollisionDetection(float aRadius, float bRadius, D3DXVECTOR2 vA, D3DXVECTOR2 vB)
{
	D3DXVECTOR2 distance = vA - vB;

	return (pow(aRadius + bRadius, 2) > D3DXVec2LengthSq(&distance));
}

//axis aligned collision
bool Physics::circleSquareCollision(GameObject* squareObj, GameObject* circleObj) {
	D3DXVECTOR2 circleDistance;
	float rectWidth = squareObj->getSpriteWidth();
	float rectHeight = squareObj->getSpriteHeight();
	float rectMidx = squareObj->getPosition().x + rectWidth / 2;
	float rectMidy = squareObj->getPosition().y + rectHeight / 2;

	float circleMidx = circleObj->getPosition().x + circleObj->getSpriteWidth() / 2;
	float circleMidy = circleObj->getPosition().y + circleObj->getSpriteHeight() / 2;

	float distanceX = abs(circleMidx - rectMidx);
	float distanceY = abs(circleMidy - rectMidy);

	if (distanceX > (rectWidth / 2 + circleObj->getSpriteWidth() / 2)) { return false; }
	if (distanceY > (rectHeight / 2 + circleObj->getSpriteWidth() / 2)) { return false; }

	if (distanceX <= (rectWidth / 2)) { return true; }
	if (distanceY <= (rectHeight / 2)) { return true; }

	float dx = distanceX - rectWidth / 2;
	float dy = distanceY - rectHeight / 2;

	return (dx * dx + dy * dy <= (circleObj->getSpriteWidth() / 2) * (circleObj->getSpriteWidth() / 2));
}

void Physics::setAirResistance(float airRes) {
	airResistance = airRes;
}

float Physics::getAirResistance() {
	return airResistance;
}

void Physics::setGravity(float newGravity) {
	gravity = newGravity;
}

float Physics::getGravity() {
	return gravity;
}

void Physics::setWindForce(float newWindForce) {
	windForce = newWindForce;
}

float Physics::getWindForce() {
	return windForce;
}

void Physics::addAirResistance(GameObject* gameObj) {
	D3DXVECTOR2 objVel = gameObj->GetVelocity();
	gameObj->SetVelocity(D3DXVECTOR2(objVel.x * airResistance, objVel.y * airResistance));
}

void Physics::addGravity(GameObject* gameObj) {
	D3DXVECTOR2 objVel = gameObj->GetVelocity();
	gameObj->SetVelocity(D3DXVECTOR2(objVel.x, objVel.y + gravity));
}

void Physics::addWindForce(GameObject* gameObj) {
	D3DXVECTOR2 objVel = gameObj->GetVelocity();
	gameObj->SetVelocity(D3DXVECTOR2(objVel.x - windForce, objVel.y));
}

void Physics::addFriction(GameObject* gameObj) {
	D3DXVECTOR2 objVel = gameObj->GetVelocity();
	gameObj->SetVelocity(D3DXVECTOR2(objVel.x * friction, objVel.y));
}