#pragma once
#include <d3dx9.h>
#include "GameObject.h"

class Physics {
	public:
		Physics(float newAirResistance, float newGravity, float newWindForce);
		Physics();

		bool circleCollisionDetection(float aRadius, float bRadius, D3DXVECTOR2 vA, D3DXVECTOR2 vB);
		bool squareCollisionDetection(GameObject& obj1, GameObject& obj2);
		bool circleSquareCollision(GameObject* squareObj, GameObject* circleObj);
		void setAirResistance(float airRes);
		float getAirResistance();
		void setGravity(float newGravity);
		float getGravity();
		void setWindForce(float newWindForce);
		float getWindForce();

		void addAirResistance(GameObject* gameObj);
		void addGravity(GameObject* gameObj);
		void addWindForce(GameObject* gameObj);
		void addFriction(GameObject* gameObj);
	private:
		float airResistance;
		float gravity;
		float windForce;
		float friction = 0.99f;
};