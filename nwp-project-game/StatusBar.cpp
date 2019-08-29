#pragma once

#include <SDL.h>
#include "StatusBar.h"
#include "TextureHelper.h"
#include "Game.h"

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

	Uint32 minutes;
	Uint32 seconds;

	minutes = Game::elapsedTime / 60000;
	Uint32 remainder = Game::elapsedTime % 60000;

	seconds = remainder / 1000;

	targetRect.x = 1088;
	targetRect.y = 0;
	targetRect.w = 192;
	targetRect.h = 64;


	std::string minutesStr;
	if (minutes <= 9)
	{
		minutesStr = "0" + std::to_string(minutes);
	}
	else
	{
		minutesStr = std::to_string(minutes);
	}

	std::string secondsStr;
	if (seconds <= 9)
	{
		secondsStr = "0" + std::to_string(seconds);
	}
	else
	{
		secondsStr = std::to_string(seconds);
	}
	texture = TextureHelper::loadFromRenderedText(minutesStr + ":" + secondsStr, { 0, 0, 0 });
	SDL_RenderCopy(Game::renderer, texture , NULL, &targetRect);
	SDL_DestroyTexture(texture);
}