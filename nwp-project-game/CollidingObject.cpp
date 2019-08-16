#pragma once

#include "CollidingObject.h"
#include <string.h>

CollidingObject::CollidingObject(int x, int y, std::string ap) : GameObject(x, y, ap) {
	setCollisionRect();
}

void CollidingObject::setCollisionRect() {
	collisionRect->w = WIDTH;
	collisionRect->h = HEIGHT;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}