#pragma once

#include "Tile.h"
#include <vector>
#include "Enemy.h"

class Level {
private:
	void clearTiles();
	void clearEnemies();
public:
	static std::vector<Tile*> tiles;
	static std::vector<Enemy*> enemies;
	static int startPosX;
	static int startPosY;

	void init(int map[12][20]);
	void update();
	void render();
	void clear();
};
