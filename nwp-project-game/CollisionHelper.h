#pragma once

#include <SDL.h>

class CollisionHelper {
public:
	static bool checkCollision(SDL_Rect *recA, SDL_Rect *recB);
};
