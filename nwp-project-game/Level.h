#pragma once

#include "Tile.h"
#include <vector>
#include "Enemy.h"

class Level {
private:
	void clearTiles();
	void clearEnemies();
public:
	Level(int map[12][20]);
	~Level();

	static std::vector<Tile*> tiles;
	static std::vector<Enemy*> enemies;
	static int startPosX;
	static int startPosY;

	void update();
	void render();
};
