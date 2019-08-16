#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Level.h"
#include "Enemy.h"
#include "MobileObject.h"
#include <string>

class Player : public MobileObject {

private:
	void animate();
public:
	void init();
	void handleEvent(SDL_Event& e);
	void update();

	void setCollisionRect();

	Player(int x, int y, std::string ap);
};
