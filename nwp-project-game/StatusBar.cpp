#include <SDL.h>
#include "StatusBar.h"
#include "TextureHelper.h"
#include "Game.h"
#include "TimeHelper.h"

void StatusBar::loadTextures() {
	lifeTexture = TextureHelper::textures["life_stationary"];
}

StatusBar::StatusBar() {
	loadTextures();
}

void StatusBar::render() {

	int tileSize = Game::SCREEN_WIDTH / 20;

	for (int i = 0; i < Game::lives; i++)
	{
		SDL_Rect targetRect;

		targetRect.x = i * tileSize;
		targetRect.y = 0;
		targetRect.w = tileSize;
		targetRect.h = tileSize;

		SDL_RenderCopy(Game::renderer, lifeTexture, NULL, &targetRect);
	}


	SDL_Rect targetRect;

	targetRect.x = 8 * tileSize;
	targetRect.y = 0;
	targetRect.w = 4 * tileSize;
	targetRect.h = tileSize;

	SDL_Texture* texture = TextureHelper::loadFromRenderedText("Level " + std::to_string(Game::currentLevel), { 0, 0, 0 });
	SDL_RenderCopy(Game::renderer, texture , NULL, &targetRect);
	SDL_DestroyTexture(texture);

	targetRect.x = Game::SCREEN_WIDTH - 3 * tileSize;
	targetRect.y = 0;
	targetRect.w = 3 * tileSize;
	targetRect.h = tileSize;

	texture = TextureHelper::loadFromRenderedText(TimeHelper::millisToString(Game::elapsedTime), { 0, 0, 0 });
	SDL_RenderCopy(Game::renderer, texture , NULL, &targetRect);
	SDL_DestroyTexture(texture);
}