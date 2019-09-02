#include "CollidingObject.h"

CollidingObject::CollidingObject(int x, int y, std::string ap) : GameObject(x, y, ap) {
	setCollisionRect();
}

void CollidingObject::setCollisionRect() {
	collisionRect->w = width;
	collisionRect->h = height;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}