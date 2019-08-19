#pragma once

#include <SDL.h>
#include "StatusBar.h"
#include "TextureHelper.h"
#include "Game.h"

void StatusBar::loadTextures() {
	lifeTexture = TextureHelper::textures["life_stationary"];
}

void StatusBar::init() {
	loadTextures();
}

void StatusBar::update() {

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
}

void StatusBar::clear() {

}