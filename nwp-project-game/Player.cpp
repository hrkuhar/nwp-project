#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Player.h"
#include "Game.h";
#include "TextureHelper.h";

void Player::init(SDL_Renderer* r) {
	renderer = r;
	loadTextures();
}

void Player::update(SDL_Surface* screenSurface) {

	applyGravity();

	positionX += velocityX;
	positionY += velocityY;

	checkBoundaries();

	
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
	return positionY + height >= Game::SCREEN_HEIGHT;
}

void Player::applyGravity() {
	if (!isOnGround())
	{
		if (velocityY < velocity && frame % 3 == 0)
		{
			velocityY += velocity / 2;
		}
	}
}

void Player::checkBoundaries() {
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
		moveRightTextures[i] = TextureHelper::loadTexture(renderer, path);
	}

	standingTexture = TextureHelper::loadTexture(renderer, "assets/player_stand.png");
	jumpingTexture = TextureHelper::loadTexture(renderer, "assets/player_jump.png");
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

	SDL_Rect stretchRect;
	stretchRect.x = positionX;
	stretchRect.y = positionY;
	stretchRect.w = width;
	stretchRect.h = height;

	SDL_RenderCopyEx(renderer, currentTexture, NULL, &stretchRect, NULL, NULL, flipTextures);

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
	SDL_DestroyTexture(jumpingTexture);
}