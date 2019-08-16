#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Level.h"
#include "Enemy.h"
#include "MobileObject.h"

class Player : public MobileObject {

private:
	SDL_Texture* moveRightTextures[4];
	SDL_Texture* standingTexture;
	SDL_Texture* jumpingTexture;

	void loadTextures();
	void animate();
public:
	void init();
	void handleEvent(SDL_Event& e);
	void update();
	void clear();

	void setCollisionRect();

	Player(int x, int y);
};
