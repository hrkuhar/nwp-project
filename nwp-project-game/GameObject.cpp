#pragma once

#include <SDL.h>
#include "GameObject.h"
#include "Game.h"
#include "TextureHelper.h"

void GameObject::render() {
	SDL_Rect targetRect;
	targetRect.x = positionX;
	targetRect.y = positionY;
	targetRect.w = WIDTH;
	targetRect.h = HEIGHT;

	SDL_RenderCopyEx(Game::renderer, texture, NULL, &targetRect, NULL, NULL, flipTextures);
}

GameObject::GameObject(int x, int y, std::string ap) {
	positionX = x;
	positionY = y;
	assetsPrefix = ap;
	setTextures();
}

void GameObject::setTextures() {
	standingTexture = TextureHelper::textures[assetsPrefix + "_stand"];
}