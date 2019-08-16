#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Level.h"

class Enemy : public Collider {

private:
	SDL_Texture* currentTexture;

	SDL_Texture* standingTexture;
	SDL_Texture* moveRightTextures[4];

	const int width = 64;
	const int height = 64;
	const int velocity = 2;

	int positionX;
	int positionY;

	int velocityX = 2;
	int velocityY = 0;

	int frame = 1;

	SDL_RendererFlip flipTextures = SDL_FLIP_NONE;

	bool isOnGround();
	void applyGravity();
	void checkBoundries();
	void loadTextures();
	void animate();
	Level* level;
public:
	void init();
	void handleEvent(SDL_Event& e);
	void update();
	void render();
	void clear();

	void setCollisionRect();

	Enemy(Level* level, int posX, int posY);

	void changeDirection();
};
