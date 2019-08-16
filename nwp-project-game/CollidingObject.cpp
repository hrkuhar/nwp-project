#pragma once

#include "CollidingObject.h"

CollidingObject::CollidingObject(int x, int y) : GameObject(x, y) {

}

void CollidingObject::setCollisionRect() {
	collisionRect->w = WIDTH;
	collisionRect->h = HEIGHT;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}