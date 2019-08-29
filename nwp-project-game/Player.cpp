#include "Player.h"
#include "Game.h"
#include "CollisionHelper.h"
#include "Level.h"

Player::Player() : MobileObject(0, 0, "player", 4, 0, 0) {

}

void Player::update() {

	applyGravity();

	if (velocityX != 0)
	{
		move(velocityX, positionX);
	}

	if (velocityY != 0)
	{
		move(velocityY, positionY);
	}

	for (int i = 0; i < Level::enemies.size(); i++)
	{
		if (CollisionHelper::checkCollision(collisionRect, Level::enemies[i]->collisionRect)) {
			setPosition(Level::startPosX, Level::startPosY);
			Game::lives--;
		}
	}

	if (isTouchingCeiling() && velocityY < 0)
	{
		velocityY = 0;
	}

	checkBoundries();
	setCollisionRect();
	animate();
}

void Player::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (isOnGround() && velocityY >= 0)
			{
				velocityY -= velocity * 5;
			}
			break;
		case SDLK_LEFT:
			flipTextures = SDL_FLIP_HORIZONTAL;
			velocityX -= velocity; 
			break;
		case SDLK_RIGHT:
			flipTextures = SDL_FLIP_NONE;
			velocityX += velocity; 
			break;
		case SDLK_ESCAPE:
			velocityX = 0;
			Game::displayMenu();
			break;
		}
		
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: 
			velocityX += velocity; 
			break;
		case SDLK_RIGHT: 
			velocityX -= velocity; 
			break;
		}
	}
}

void Player::animate() {
	if (!isOnGround())
	{
		texture = jumpingTexture;
	}
	else if (velocityX != 0)
	{
		texture = moveTextures[(Game::frame / 4) % 4];
	}
	else {
		texture = standingTexture;
	}
}

void Player::setCollisionRect() {
	collisionRect->w = WIDTH / 2;
	collisionRect->h = HEIGHT;
	collisionRect->x = positionX + WIDTH / 4;
	collisionRect->y = positionY;
}

void Player::setPosition(int x, int y) {
	positionX = x;
	positionY = y;
	setCollisionRect();
}

bool Player::isOnGround() {
	SDL_Rect testRect;
	testRect.h = collisionRect->h;
	testRect.w = collisionRect->w;
	testRect.x = collisionRect->x;
	testRect.y = collisionRect->y + 1;

	for (int i = 0; i < Level::tiles.size(); i++)
	{
		if ((CollisionHelper::checkCollision(&testRect, Level::tiles[i]->collisionRect) && Level::tiles[i]->type == "brick")) {
			return true;
		}
	}
	return false;
}

void Player::move(int vel, int& position) {

	int step = vel > 0 ? 1 : -1;

	for (int y = 0; y < std::abs(vel); y++)
	{
		position += step;
		setCollisionRect();

		for (int i = 0; i < Level::tiles.size(); i++)
		{
			if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
				if (Level::tiles[i]->type == "spike")
				{
					setPosition(Level::startPosX, Level::startPosY);
					Game::lives--;
				}
				else if (Level::tiles[i]->type == "level_end")
				{
					Game::nextLevel();
				}
				else if(Level::tiles[i]->type != "level_start")
				{
					position -= step;
					setCollisionRect();
					break;
				}

			}
		}
	}
}
