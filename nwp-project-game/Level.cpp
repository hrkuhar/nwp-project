#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Level.h"
#include "TextureHelper.h"
#include "Game.h"
#include <vector>
#include "CollisionHelper.h"
#include <iterator>

Enemy *enemy1 = nullptr;
Enemy *enemy2 = nullptr;
std::vector<Enemy*> Level::enemies;
std::vector<Tile*> Level::tiles;

void Level::init() {
	loadTextures();

	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (map[i][j] == 1)
			{
				Tile* tile = new Tile(j * 64, i * 64, "tile");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
		}
	}

	enemy1 = new Enemy(150, 150, "enemy");
	enemy1->init();

	enemy2 = new Enemy(500, 500, "enemy");
	enemy2->init();

	enemies.push_back(enemy1);
	enemies.push_back(enemy2);
}

void Level::loadTextures() {
	tileTexture = TextureHelper::loadTexture(Game::renderer, "assets/tile_brick.png");
}

void Level::update() {
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
	}
}

void Level::render()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->render();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render();
	}
}

void Level::clear()
{
	SDL_DestroyTexture(tileTexture);
}