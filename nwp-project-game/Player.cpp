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

Player::Player(int x, int y, std::string ap) : MobileObject(x, y, ap, 4, 0, 0) {

}

void Player::init() {

}

void Player::update() {

	applyGravity();

	if (velocityX > 0)
	{
		for (int x = 0; x < velocityX; x++)
		{
			positionX += 1;
			setCollisionRect();

			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
					if (Level::tiles[i]->type == "spike")
					{
						positionX = Level::startPosX;
						positionY = Level::startPosY;
						setCollisionRect();
					}
					else if (Level::tiles[i]->type == "level_start")
					{

					}
					else if (Level::tiles[i]->type == "level_end")
					{
						printf("LEVEL END");
					}
					else
					{
						positionX -= 1;
						setCollisionRect();
						break;
					}					
					
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

			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
					if (Level::tiles[i]->type == "spike")
					{
						positionX = Level::startPosX;
						positionY = Level::startPosY;
						setCollisionRect();
					}
					else if (Level::tiles[i]->type == "level_start")
					{
						
					}
					else if (Level::tiles[i]->type == "level_end")
					{
						printf("LEVEL END");
					}
					else
					{
						positionX += 1;
						setCollisionRect();
						break;
					}					
					
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

			for (int i = 0; i < Level::tiles.size(); i++)
			{
				if (CollisionHelper::checkCollision(collisionRect, Level::tiles[i]->collisionRect)) {
					if (Level::tiles[i]->type == "spike")
					{
						positionX = Level::startPosX;
						positionY = Level::startPosY;
						setCollisionRect();
					}
					else if (Level::tiles[i]->type == "level_start")
					{

					}
					else if (Level::tiles[i]->type == "level_end")
					{
						printf("LEVEL END");

					}
					else
					{
						positionY -= 1;
						setCollisionRect();
						break;
					}					
					
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
					if (Level::tiles[i]->type == "spike")
					{
						positionX = Level::startPosX;
						positionY = Level::startPosY;
						setCollisionRect();
					}
					else if (Level::tiles[i]->type == "level_start")
					{

					}
					else if (Level::tiles[i]->type == "level_end")
					{
						printf("LEVEL END");
					}
					else
					{
						positionY += 1;
						setCollisionRect();
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < Level::enemies.size(); i++)
	{
		if (CollisionHelper::checkCollision(collisionRect, Level::enemies[i]->collisionRect)) {
			positionX = Level::startPosX;
			positionY = Level::startPosY;
		}
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
