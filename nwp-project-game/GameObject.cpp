#include <SDL.h>
#include "GameObject.h"
#include "Game.h"
#include "TextureHelper.h"

void GameObject::render() {
	SDL_Rect targetRect;
	targetRect.x = positionX;
	targetRect.y = positionY;
	targetRect.w = width;
	targetRect.h = height;

	SDL_RenderCopyEx(Game::renderer, texture, NULL, &targetRect, NULL, NULL, flipTextures);
}

GameObject::GameObject(int x, int y, std::string ap) {
	height = Game::SCREEN_WIDTH / 20;
	width = Game::SCREEN_WIDTH / 20;
	positionX = x;
	positionY = y;
	assetsPrefix = ap;
	setTextures();
}

void GameObject::setTextures() {
	standingTexture = TextureHelper::textures[assetsPrefix + "_stationary"];
}