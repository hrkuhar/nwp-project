#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Level.h"
#include "Enemy.h"
#include "Collider.h"

class Player : public GameObject, public Collider {

private:
	SDL_Texture* moveRightTextures[4];
	SDL_Texture* standingTexture;
	SDL_Texture* jumpingTexture;

	const int velocity = 4;

	int velocityX = 0;
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

	std::string type;
	std::string subtype;

	void setCollisionRect();

	Player(int x, int y);
};
