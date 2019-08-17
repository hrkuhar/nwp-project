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
int Level::startPosX;
int Level::startPosY;

void Level::init() {
	loadTextures();

	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (map[i][j] == 1)
			{
				Tile* tile = new Tile(j * 64, i * 64, "brick", "brick");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == 2)
			{
				Tile* tile = new Tile(j * 64, i * 64, "spike", "spike");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == 6)
			{
				Enemy* enemy = new Enemy(j * 64, i * 64 - 1, "enemy", NULL);
				enemy->init();
				enemies.push_back(enemy);
			}
			else if (map[i][j] == 7)
			{
				Enemy* enemy = new Enemy(j * 64, i * 64 - 1, "enemy_bouncer", 6);
				enemy->init();
				enemies.push_back(enemy);
			}
			else if (map[i][j] == 5)
			{
				startPosX = j * 64;
				startPosY = i * 64 - 1;
				Game::player->setPosition(startPosX, startPosY);

				Tile* tile = new Tile(j * 64, i * 64, "level_start", "level_start");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
			else if (map[i][j] == 3)
			{
				Tile* tile = new Tile(j * 64, i * 64, "level_end", "level_end");
				tile->setCollisionRect();
				tiles.push_back(tile);
			}
		}
	}
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