#pragma once

#include <SDL.h>

class Collider {
public:
	SDL_Rect* collisionRect = new SDL_Rect();
	virtual void setCollisionRect() = 0;
};
