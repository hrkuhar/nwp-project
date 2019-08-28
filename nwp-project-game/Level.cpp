#pragma once

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

void Level::init(int map[12][20]) {

	statusBar = new StatusBar();
	statusBar->init();

	clearTiles();
	clearEnemies();

	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (map[i][j] == BRICK)
			{
				Tile* tile = new Tile(j * 64, (i + 1) * 64, "brick", "brick");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == SPIKES)
			{
				Tile* tile = new Tile(j * 64, (i + 1) * 64, "spike", "spike");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == LEVEL_START)
			{
				startPosX = j * 64;
				startPosY = (i + 1) * 64;
				Game::player->setPosition(startPosX, startPosY);

				Tile* tile = new Tile(j * 64, (i + 1) * 64, "level_start", "level_start");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == LEVEL_END)
			{
				Tile* tile = new Tile(j * 64, (i + 1) * 64, "level_end", "level_end");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == ENEMY_BASIC)
			{
				Enemy* enemy = new Enemy(j * 64, (i + 1) * 64, "enemy", NULL);
				enemy->init();
				enemies.push_back(enemy);
			}
			else if (map[i][j] == ENEMY_BOUNCER_HEAVY)
			{
				Enemy* enemy = new Enemy(j * 64, (i + 1) * 64, "enemy_bouncer", 6);
				enemy->init();
				enemies.push_back(enemy);
			}
			else if (map[i][j] == ENEMY_BOUNCER_MEDIUM)
			{
				Enemy* enemy = new Enemy(j * 64, (i + 1) * 64, "enemy_bouncer", 8);
				enemy->init();
				enemies.push_back(enemy);
			}
			else if (map[i][j] == ENEMY_BOUNCER_LIGHT)
			{
				Enemy* enemy = new Enemy(j * 64, (i + 1) * 64, "enemy_bouncer", 10);
				enemy->init();
				enemies.push_back(enemy);
			}
		}
	}
}

void Level::update() {
	statusBar->update();
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

void Level::clear() {
	delete statusBar;
	statusBar = NULL;

	clearTiles();
	clearEnemies();
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