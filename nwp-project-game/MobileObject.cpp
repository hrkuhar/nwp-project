#pragma once

#include "MobileObject.h"
#include "Level.h"
#include "CollisionHelper.h"
#include "Game.h"
#include "TextureHelper.h"
#include <string>

MobileObject::MobileObject(int x, int y, std::string ap, int vel, int velX, int velY) : CollidingObject(x, y, ap) {
	velocity = vel;
	velocityX = velX;
	velocityY = velY;
	setTextures();
}

bool MobileObject::isOnGround() {
	SDL_Rect testRect;
	testRect.h = collisionRect->h;
	testRect.w = collisionRect->w;
	testRect.x = collisionRect->x;
	testRect.y = collisionRect->y + 1;

	for (int i = 0; i < Level::tiles.size(); i++)
	{
		if ((CollisionHelper::checkCollision(&testRect, Level::tiles[i]->collisionRect))) {
			return true;
		}
	}
	return false;
}

bool MobileObject::isTouchingCeiling() {
	SDL_Rect testRect;
	testRect.h = collisionRect->h;
	testRect.w = collisionRect->w;
	testRect.x = collisionRect->x;
	testRect.y = collisionRect->y - 1;

	for (int i = 0; i < Level::tiles.size(); i++)
	{
		if ((CollisionHelper::checkCollision(&testRect, Level::tiles[i]->collisionRect) && Level::tiles[i]->type == "brick")) {
			return true;
		}
	}
	return false;
}

void MobileObject::applyGravity() {
	if (!isOnGround())
	{
		if (velocityY < velocity * 2)
		{
			velocityY += 1;
		}
	}
	else
	{
		if (velocityY > 0)
		{
			velocityY = 0;
		}
	}
}

void MobileObject::checkBoundries() {
	if (positionY + HEIGHT >= Game::SCREEN_HEIGHT)
	{
		positionY = Game::SCREEN_HEIGHT - HEIGHT;
	}
	if (positionX < 1)
	{
		positionX = 1;
	}
	if (positionX + WIDTH >= Game::SCREEN_WIDTH)
	{
		positionX = Game::SCREEN_WIDTH - WIDTH;
	}
}

void MobileObject::setTextures() {
	GameObject::setTextures();
	jumpingTexture = TextureHelper::textures[assetsPrefix + "_jump"];
	for (int i = 0; i < 4; i++)
	{
		moveTextures[i] = TextureHelper::textures[assetsPrefix + "_move_" + std::to_string(i + 1)];
	}
}