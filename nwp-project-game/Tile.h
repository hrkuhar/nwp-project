#pragma once

#include <SDL.h>
#include <string>
#include "Collider.h"

class Tile : public Collider {

public:
	SDL_Texture* texture;

	const int width = 64;
	const int height = 64;

	int positionX;
	int positionY;

	void setCollisionRect();

};
