#include "Enemy.h"
#include "Game.h"
#include "CollisionHelper.h"
#include "Level.h"

Enemy::Enemy(int x, int y, std::string ap, int jump) : MobileObject(x, y, ap, 2, 2, 0) {
	jumpHeight = jump;
}

void Enemy::update() {

	applyGravity();

	positionX += velocityX;
	setCollisionRect();

	if (velocityX != 0)
	{
			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i].collisionRect)) {
					changeDirection();
					break;
				}
			}
		
	}

	if (velocityY != 0)
	{
		int step = velocityY > 0 ? 1 : -1;

		for (int y = 0; y < std::abs(velocityY); y++)
		{
			positionY += step;
			setCollisionRect();

			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i].collisionRect)) {
					positionY -= step;
					setCollisionRect();
					break;
				}
			}
		}
	}
	
	for (int i = 0; i < Level::enemies.size(); ++i)
	{
		if (this != &Level::enemies[i] && CollisionHelper::checkCollision(this->collisionRect, Level::enemies[i].collisionRect))
		{
			positionX -= velocityX;
			positionY -= velocityY;

			if (velocityY < 0)
			{
				velocityY = jumpHeight / 2;
			}
			else if (velocityY > 0)
			{
				velocityY = -jumpHeight / 2;
			}
			changeDirection();
		}
	}

	if (jumpHeight != NULL && jumpHeight != 0 && isOnGround())
	{
		velocityY = -velocity * jumpHeight;
	}

	if (isTouchingCeiling() && velocityY < 0)
	{
		velocityY = 0;
	}

	checkBoundries();

	setCollisionRect();

	animate();
}

void Enemy::animate() {
	if (!isOnGround())
	{
		texture = jumpingTexture;
	}
	else if (velocityX != 0)
	{
		texture = moveTextures[(Game::frame / 4) % 4];
	}
	else {
		texture = moveTextures[0];
	}
}

void Enemy::changeDirection() {
	positionX -= velocityX;
	velocityX = -velocityX;
	setCollisionRect();
	flipTextures = flipTextures == SDL_FLIP_HORIZONTAL ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}
