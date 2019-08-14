#pragma once

#include <SDL.h>
#include<string>

class Tile {

public:
	SDL_Texture* texture;

	const int width = 64;
	const int height = 64;

	int positionX;
	int positionY;

	SDL_Rect* collisionRect = new SDL_Rect();
};
