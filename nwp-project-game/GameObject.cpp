#pragma once

#include <SDL.h>
#include "GameObject.h"
#include "Game.h"

void GameObject::render() {
	SDL_Rect targetRect;
	targetRect.x = positionX;
	targetRect.y = positionY;
	targetRect.w = WIDTH;
	targetRect.h = HEIGHT;

	SDL_RenderCopyEx(Game::renderer, texture, NULL, &targetRect, NULL, NULL, flipTextures);
}

GameObject::GameObject(int x, int y) {
	positionX = x;
	positionY = y;
}