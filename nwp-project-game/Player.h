#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Level.h"
#include "Enemy.h"
#include "Collider.h"

class Player : public Collider {

private:
	SDL_Texture* currentTexture;

	SDL_Texture* moveRightTextures[4];
	SDL_Texture* standingTexture;
	SDL_Texture* jumpingTexture;

	const int width = 64;
	const int height = 64;
	const int velocity = 4;

	int positionX = 70;
	int positionY = 70;

	int velocityX = 0;
	int velocityY = 0;

	int frame = 1;

	SDL_RendererFlip flipTextures = SDL_FLIP_NONE;

	bool isOnGround();
	void applyGravity();
	void checkBoundries();
	void loadTextures();
	void animate();
	Level* level;


	std::vector<Enemy*> enemies;

public:
	void init();
	void handleEvent(SDL_Event& e);
	void update();
	void render();
	void clear();

	std::string type;
	std::string subtype;

	void setCollisionRect();

	Player(Level* level, std::vector<Enemy*> e);
};
