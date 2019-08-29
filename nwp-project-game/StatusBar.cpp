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
	for (int i = 0; i < Game::lives; i++)
	{
		SDL_Rect targetRect;

		targetRect.x = i * 64;
		targetRect.y = 0;
		targetRect.w = 64;
		targetRect.h = 64;

		SDL_RenderCopy(Game::renderer, lifeTexture, NULL, &targetRect);
	}


	SDL_Rect targetRect;

	targetRect.x = 512;
	targetRect.y = 0;
	targetRect.w = 256;
	targetRect.h = 64;

	SDL_Texture* texture = TextureHelper::loadFromRenderedText("Level " + std::to_string(Game::currentLevel), { 0, 0, 0 });
	SDL_RenderCopy(Game::renderer, texture , NULL, &targetRect);
	SDL_DestroyTexture(texture);

	targetRect.x = 1088;
	targetRect.y = 0;
	targetRect.w = 192;
	targetRect.h = 64;

	texture = TextureHelper::loadFromRenderedText(TimeHelper::millisToString(Game::elapsedTime), { 0, 0, 0 });
	SDL_RenderCopy(Game::renderer, texture , NULL, &targetRect);
	SDL_DestroyTexture(texture);
}