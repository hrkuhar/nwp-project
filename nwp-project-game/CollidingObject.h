#pragma once

#include "GameObject.h"

class CollidingObject : public GameObject {
public:
	SDL_Rect* collisionRect = new SDL_Rect();

	virtual void setCollisionRect();
	CollidingObject(int x, int y, std::string ap);
};
