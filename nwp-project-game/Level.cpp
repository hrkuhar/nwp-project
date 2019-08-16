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
				Tile tile;

				tile.positionX = j * 64;
				tile.positionY = i * 64;
				tile.texture = tileTexture;

				tile.setCollisionRect();

				tiles.push_back(tile);

				SDL_Rect targetRect;
				targetRect.x = j * 64;
				targetRect.y = i * 64;
				targetRect.w = 64;
				targetRect.h = 64;

				SDL_RenderCopy(Game::renderer, tileTexture, NULL, &targetRect);
			}
		}
	}	
}


void Level::clear()
{
	SDL_DestroyTexture(tileTexture);
}