#include "Level.h"
#include "Game.h"
#include "StatusBar.h"

std::vector<Enemy*> Level::enemies;
std::vector<Tile*> Level::tiles;
StatusBar* statusBar = nullptr;
int Level::startPosX;
int Level::startPosY;

enum Tiles {
	BLANK,
	BRICK,
	SPIKES,
	LEVEL_START,
	LEVEL_END,
	ENEMY_BASIC,
	ENEMY_BOUNCER_HEAVY,
	ENEMY_BOUNCER_MEDIUM,
	ENEMY_BOUNCER_LIGHT
};

Level::Level(int map[12][20]) {

	statusBar = new StatusBar();

	clearTiles();
	clearEnemies();

	int tileSize = Game::SCREEN_WIDTH / 20;

	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (map[i][j] == BRICK)
			{
				Tile* tile = new Tile(j * tileSize, (i + 1) * tileSize, "brick", "brick");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == SPIKES)
			{
				Tile* tile = new Tile(j * tileSize, (i + 1) * tileSize, "spike", "spike");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == LEVEL_START)
			{
				startPosX = j * tileSize;
				startPosY = (i + 1) * tileSize;
				Game::player->setPosition(startPosX, startPosY);

				Tile* tile = new Tile(j * tileSize, (i + 1) * tileSize, "level_start", "level_start");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == LEVEL_END)
			{
				Tile* tile = new Tile(j * tileSize, (i + 1) * tileSize, "level_end", "level_end");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == ENEMY_BASIC)
			{
				Enemy* enemy = new Enemy(j * tileSize, (i + 1) * tileSize, "enemy", NULL);
				enemies.push_back(enemy);
			}
			else if (map[i][j] == ENEMY_BOUNCER_HEAVY)
			{
				Enemy* enemy = new Enemy(j * tileSize, (i + 1) * tileSize, "enemy_bouncer", 6);
				enemies.push_back(enemy);
			}
			else if (map[i][j] == ENEMY_BOUNCER_MEDIUM)
			{
				Enemy* enemy = new Enemy(j * tileSize, (i + 1) * tileSize, "enemy_bouncer", 8);
				enemies.push_back(enemy);
			}
			else if (map[i][j] == ENEMY_BOUNCER_LIGHT)
			{
				Enemy* enemy = new Enemy(j * tileSize, (i + 1) * tileSize, "enemy_bouncer", 10);
				enemies.push_back(enemy);
			}
		}
	}
}

void Level::update() {
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
	}
}

void Level::render()
{
	statusBar->render();
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->render();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render();
	}
}

void Level::clearTiles() {
	std::vector<Tile*>::iterator it;
	for (it = tiles.begin(); it != tiles.end(); it++)
	{
		delete *it;
	}

	tiles.clear();
}

void Level::clearEnemies() {
	std::vector<Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		delete *it;
	}

	enemies.clear();
}

Level::~Level() {
	delete statusBar;
	statusBar = NULL;

	clearTiles();
	clearEnemies();
}