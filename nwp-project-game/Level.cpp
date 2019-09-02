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

Level::Level(std::string map) {

	statusBar = new StatusBar();

	clearTiles();
	clearEnemies();

	int row = 0;
	int column = 0;
	for (int i = 0; i < map.size(); i++)
	{
		char c = map[i];
		int code;

		if (c == '\n')
		{
			column = 0;
			++row;
			continue;
		}
		else if (c == ' ')
		{
			continue;
		}
		else
		{
			code = c - 48;
		}

		if (code == BRICK)
		{
			Tile* tile = new Tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "brick", "brick");
			tile->setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == SPIKES)
		{
			Tile* tile = new Tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "spike", "spike");
			tile->setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == LEVEL_START)
		{
			startPosX = column * Game::TILE_SIZE;
			startPosY = (row + 1) * Game::TILE_SIZE;
			Game::player->setPosition(startPosX, startPosY);

			Tile* tile = new Tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "level_start", "level_start");
			tile->setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == LEVEL_END)
		{
			Tile* tile = new Tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "level_end", "level_end");
			tile->setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == ENEMY_BASIC)
		{
			Enemy* enemy = new Enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy", NULL);
			enemies.push_back(enemy);
		}
		else if (code == ENEMY_BOUNCER_HEAVY)
		{
			Enemy* enemy = new Enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy_bouncer", 6);
			enemies.push_back(enemy);
		}
		else if (code == ENEMY_BOUNCER_MEDIUM)
		{
			Enemy* enemy = new Enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy_bouncer", 8);
			enemies.push_back(enemy);
		}
		else if (code == ENEMY_BOUNCER_LIGHT)
		{
			Enemy* enemy = new Enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy_bouncer", 10);
			enemies.push_back(enemy);
		}
		++column;
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