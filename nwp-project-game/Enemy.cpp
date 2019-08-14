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

void Enemy::init(SDL_Renderer* r) {
	renderer = r;
	loadTextures();

	collisionRect = new  SDL_Rect();

	collisionRect->w = width;
	collisionRect->h = height;

	setCOllisionRect();
}

void Enemy::update() {

	applyGravity();

	positionX += velocityX;
	setCOllisionRect();

	if (velocityX != 0)
	{
			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
					positionX -= velocityX;
					velocityX = -velocityX;
					setCOllisionRect();
					break;
				}
			}
		
	}


	if (velocityY > 0)
	{
		for (int y = 0; y < velocityY; y++)
		{
			positionY += 1;
			setCOllisionRect();

			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
					positionY -= 1;
					setCOllisionRect();
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
			setCOllisionRect();

			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
					positionY += 1;
					setCOllisionRect();
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

	setCOllisionRect();
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
		if (velocityY < velocity * 2 && frame % 3 == 0)
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
	if (positionY + height >= Game::SCREEN_HEIGHT)
	{
		positionY = Game::SCREEN_HEIGHT - height;
	}
	if (positionX < 1)
	{
		positionX = 1;
	}
	if (positionX + width >= Game::SCREEN_WIDTH)
	{
		positionX = Game::SCREEN_WIDTH - width;
	}
}

void Enemy::loadTextures() {
	standingTexture = TextureHelper::loadTexture(renderer, "assets/enemy.png");
}

void Enemy::animate() {
	currentTexture = standingTexture;
}

void Enemy::render() {
	animate();

	SDL_Rect targetRect;
	targetRect.x = positionX;
	targetRect.y = positionY;
	targetRect.w = width;
	targetRect.h = height;

	SDL_RenderCopyEx(renderer, currentTexture, NULL, &targetRect, NULL, NULL, flipTextures);

	++frame;
}

void Enemy::clear()
{
	SDL_DestroyTexture(standingTexture);
	standingTexture = NULL;
}

void Enemy::setCOllisionRect() {
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}
