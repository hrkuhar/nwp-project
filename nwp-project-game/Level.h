#pragma once

#include "Tile.h"
#include <vector>
#include "Enemy.h"

class Level {
private:
	void clearTiles();
	void clearEnemies();
public:
	Level(std::string level);
	~Level();

	static std::vector<Tile*> tiles;
	static std::vector<Enemy*> enemies;
	static int startPosX;
	static int startPosY;

	void update();
	void render();
};
