#include "Level.h"
#include "Game.h"
#include "StatusBar.h"

std::vector<Enemy> Level::enemies;
std::vector<Tile> Level::tiles;
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

	tiles.clear();
	enemies.clear();

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
			Tile tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "brick", "brick");
			tile.setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == SPIKES)
		{
			Tile tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "spike", "spike");
			tile.setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == LEVEL_START)
		{
			startPosX = column * Game::TILE_SIZE;
			startPosY = (row + 1) * Game::TILE_SIZE;
			Game::player->setPosition(startPosX, startPosY);

			Tile tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "level_start", "level_start");
			tile.setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == LEVEL_END)
		{
			Tile tile(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "level_end", "level_end");
			tile.setCollisionRect();
			tiles.push_back(tile);
		}
		else if (code == ENEMY_BASIC)
		{
			Enemy enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy", NULL);
			enemies.push_back(enemy);
		}
		else if (code == ENEMY_BOUNCER_HEAVY)
		{
			Enemy enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy_bouncer", 6);
			enemies.push_back(enemy);
		}
		else if (code == ENEMY_BOUNCER_MEDIUM)
		{
			Enemy enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy_bouncer", 8);
			enemies.push_back(enemy);
		}
		else if (code == ENEMY_BOUNCER_LIGHT)
		{
			Enemy enemy(column * Game::TILE_SIZE, (row + 1) * Game::TILE_SIZE, "enemy_bouncer", 10);
			enemies.push_back(enemy);
		}
		++column;
	}
}

void Level::update() {
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].update();
	}
}

void Level::render()
{
	statusBar->render();
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].render();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].render();
	}
}

Level::~Level() {
	delete statusBar;
	statusBar = NULL;

	tiles.clear();
	enemies.clear();
}