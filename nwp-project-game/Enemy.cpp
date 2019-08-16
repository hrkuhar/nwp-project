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

Enemy::Enemy(Level* l, int posX, int posY) {
	level = l;
	positionX = posX;
	positionY = posY;
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
			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
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

			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
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

			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
					positionY += 1;
					setCollisionRect();
					break;
				}
			}
		}
	}

	/*positionX += velocityX;
	positionY += velocityY;

	setCOllisionRect();

	for (int i = 0; i < level->tiles.size(); i++)
	{
		if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {

			positionX -= velocityX;
			positionY -= velocityY;

			setCOllisionRect();

			break;
		}
	}*/

	checkBoundries();

	setCollisionRect();
}


void Enemy::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (isOnGround())
			{
				velocityY -= velocity * 4;
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

bool Enemy::isOnGround() {
	SDL_Rect testRect;
	testRect.h = collisionRect->h;
	testRect.w = collisionRect->w;
	testRect.x = collisionRect->x;
	testRect.y = collisionRect->y + 1;

	for (int i = 0; i < level->tiles.size(); i++)
	{
		if (CollisionHelper::checkCollision(&testRect, level->tiles[i].collisionRect)) {
			return true;
		}
	}
	return false;
}

void Enemy::applyGravity() {
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

void Enemy::checkBoundries() {
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

void Enemy::render() {
	animate();
	GameObject::render();
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

void Enemy::setCollisionRect() {
	collisionRect->w = WIDTH;
	collisionRect->h = HEIGHT;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}

void Enemy::changeDirection() {
	positionX -= velocityX;
	velocityX = -velocityX;
	setCollisionRect();
	flipTextures = flipTextures == SDL_FLIP_HORIZONTAL ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}
