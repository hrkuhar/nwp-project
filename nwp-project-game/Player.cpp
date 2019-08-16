#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Player.h"
#include "Game.h";
#include "TextureHelper.h";
#include <vector>
#include "Tile.h"
#include "CollisionHelper.h"
#include "Level.h"

Player::Player(Level* l, std::vector<Enemy*> e) {
	level = l;
	enemies = e;
}

void Player::init() {
	loadTextures();
	setCollisionRect();
}

void Player::update() {

	applyGravity();

	if (velocityX > 0)
	{
		for (int x = 0; x < velocityX; x++)
		{
			positionX += 1;
			setCollisionRect();

			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
					positionX -= 1;
					setCollisionRect();
					break;
				}
			}
		}
	}

	if (velocityX < 0)
	{
		for (int x = 0; x > velocityX; x--)
		{
			positionX -= 1;
			setCollisionRect();

			for (int i = 0; i < level->tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, level->tiles[i].collisionRect)) {
					positionX += 1;
					setCollisionRect();
					break;
				}
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

	for (int i = 0; i < enemies.size(); i++)
	{
		if (CollisionHelper::checkCollision(collisionRect, enemies[i]->collisionRect)) {
			positionX = 70;
			positionY = 70;
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


void Player::handleEvent(SDL_Event& e) {
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

bool Player::isOnGround() {
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

void Player::applyGravity() {
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

void Player::checkBoundries() {
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

void Player::loadTextures() {

	for (int i = 0; i < 4; i++)
	{
		std::string path = "assets/player_move_right_" + std::to_string(i + 1) + ".png";
		moveRightTextures[i] = TextureHelper::loadTexture(Game::renderer, path);
	}

	standingTexture = TextureHelper::loadTexture(Game::renderer, "assets/player_stand.png");
	jumpingTexture = TextureHelper::loadTexture(Game::renderer, "assets/player_jump.png");
}

void Player::animate() {
	if (!isOnGround())
	{
		currentTexture = jumpingTexture;
	}
	else if (velocityX != 0)
	{
		currentTexture = moveRightTextures[(frame / 4) % 4];
	}
	else {
		currentTexture = standingTexture;
	}
}

void Player::render() {
	animate();

	SDL_Rect targetRect;
	targetRect.x = positionX;
	targetRect.y = positionY;
	targetRect.w = width;
	targetRect.h = height;

	SDL_RenderCopyEx(Game::renderer, currentTexture, NULL, &targetRect, NULL, NULL, flipTextures);

	++frame;
}

void Player::clear()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(moveRightTextures[i]);
		moveRightTextures[i] = NULL;
	}

	SDL_DestroyTexture(standingTexture);
	standingTexture = NULL;

	SDL_DestroyTexture(jumpingTexture);
	jumpingTexture = NULL;
}

void Player::setCollisionRect() {
	collisionRect->w = width / 2;
	collisionRect->h = height;
	collisionRect->x = positionX + width / 4;
	collisionRect->y = positionY;
}
