#pragma once

#include <SDL.h>
#include "CollidingObject.h"

class MobileObject : public CollidingObject {
protected:
	int velocity;
	int velocityX;
	int velocityY;
	bool isOnGround();
	void applyGravity();
	void checkBoundries();
public:
	MobileObject(int x, int y, int vel, int velX, int velY);
};

