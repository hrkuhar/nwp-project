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
	void animate();
	int jumpHeight;
public:
	void init();
	void update();

	Enemy(int posX, int posY, std::string ap, int jump);

	void changeDirection();
};
