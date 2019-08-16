#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Collider.h"
#include "GameObject.h"

class Enemy : public GameObject, public Collider {

private:

	SDL_Texture* standingTexture;
	SDL_Texture* moveRightTextures[4];

	const int velocity = 2;

	int velocityX = 2;
	int velocityY = 0;


	bool isOnGround();
	void applyGravity();
	void checkBoundries();
	void loadTextures();
	void animate();
public:
	void init();
	void handleEvent(SDL_Event& e);
	void update();
	void clear();

	void setCollisionRect();

	Enemy(int posX, int posY);

	void changeDirection();
};
