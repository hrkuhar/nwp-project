#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Level.h"
#include "TextureHelper.h"
#include "Game.h"

void Level::init() {
	loadTextures();
}

void Level::loadTextures() {
	tileTexture = TextureHelper::loadTexture(Game::renderer, "assets/tile_brick.png");
}

void Level::render()
{
	tiles.clear();

	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			if (map[i][j] == 1)
			{
				Tile* tile = new Tile(j * 64, i * 64, tileTexture);
				tile->setCollisionRect();
				tiles.push_back(*tile);
				tile->render();
			}
		}
	}	
}


void Level::clear()
{
	SDL_DestroyTexture(tileTexture);
}