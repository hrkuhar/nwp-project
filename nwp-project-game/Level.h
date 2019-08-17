#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Tile.h"
#include <vector>
#include "Enemy.h"

class Level {

private:
	SDL_Texture* tileTexture;

	void loadTextures();
public:
	void init(int map[12][20]);
	void update();
	void render();
	void clear();

	static std::vector<Tile*> tiles;
	static std::vector<Enemy*> enemies;
	static int startPosX;
	static int startPosY;
};
