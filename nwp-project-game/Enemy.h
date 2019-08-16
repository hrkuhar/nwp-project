#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "MobileObject.h"
#include "GameObject.h"

class Enemy : public MobileObject {

private:

	SDL_Texture* standingTexture;
	SDL_Texture* moveRightTextures[4];

	void loadTextures();
	void animate();
public:
	void init();
	void update();
	void clear();

	Enemy(int posX, int posY);

	void changeDirection();
};
