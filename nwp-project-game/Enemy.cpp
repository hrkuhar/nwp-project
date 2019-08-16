#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Enemy.h"
#include "Game.h";
#include "TextureHelper.h";
#include <vector>
#include "Tile.h"
#include "CollisionHelper.h"
#include "Level.h"

Enemy::Enemy(int x, int y) : MobileObject(x, y, 2, 2, 0) {

}


void Enemy::init() {
	loadTextures();
	setCollisionRect();
}

void Enemy::update() {

	applyGravity();

	positionX += velocityX;
	setCollisionRect();

	if (velocityX != 0)
	{
			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
					changeDirection();
					break;
				}
			}
		
	}


	if (velocityY > 0)
	{
		for (int y = 0; y < velocityY; y++)
		{
			positionY += 1;
			setCollisionRect();

			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
					positionY -= 1;
					setCollisionRect();
					break;
				}
			}
		}
	}

	if (velocityY < 0)
	{
		for (int y = 0; y > velocityY; y--)
		{
			positionY -= 1;
			setCollisionRect();

			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
					positionY += 1;
					setCollisionRect();
					break;
				}
			}
		}
	}

	
	for (int i = 0; i < Level::enemies.size(); ++i)
	{
		if (this != Level::enemies[i] && CollisionHelper::checkCollision(this->collisionRect, Level::enemies[i]->collisionRect))
		{
			changeDirection();
		}
	}
	

	checkBoundries();

	setCollisionRect();

	animate();
}

void Enemy::loadTextures() {

	for (int i = 0; i < 4; i++)
	{
		std::string path = "assets/enemy_move_" + std::to_string(i + 1) + ".png";
		moveRightTextures[i] = TextureHelper::loadTexture(Game::renderer, path);
	}

	standingTexture = TextureHelper::loadTexture(Game::renderer, "assets/enemy.png");
}

void Enemy::animate() {
	if (!isOnGround())
	{
		texture = moveRightTextures[0];
	}
	else if (velocityX != 0)
	{
		texture = moveRightTextures[(Game::frame / 4) % 4];
	}
	else {
		texture = moveRightTextures[0];;
	}
}

void Enemy::clear()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(moveRightTextures[i]);
		moveRightTextures[i] = NULL;
	}

	SDL_DestroyTexture(standingTexture);
	standingTexture = NULL;
}

void Enemy::changeDirection() {
	positionX -= velocityX;
	velocityX = -velocityX;
	setCollisionRect();
	flipTextures = flipTextures == SDL_FLIP_HORIZONTAL ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}
