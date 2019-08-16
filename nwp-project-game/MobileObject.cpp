#pragma once

#include "MobileObject.h"
#include "Level.h"
#include "CollisionHelper.h"
#include "Game.h"

MobileObject::MobileObject(int x, int y, int vel, int velX, int velY) : CollidingObject(x, y) {
	velocity = vel;
	velocityX = velX;
	velocityY = velY;
}

bool MobileObject::isOnGround() {
	SDL_Rect testRect;
	testRect.h = collisionRect->h;
	testRect.w = collisionRect->w;
	testRect.x = collisionRect->x;
	testRect.y = collisionRect->y + 1;

	for (int i = 0; i < Level::tiles.size(); i++)
	{
		if (CollisionHelper::checkCollision(&testRect, Level::tiles[i]->collisionRect)) {
			return true;
		}
	}
	return false;
}

void MobileObject::applyGravity() {
	if (!isOnGround())
	{
		if (velocityY < velocity * 2 && Game::frame % 3 == 0)
		{
			velocityY += velocity / 2;
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