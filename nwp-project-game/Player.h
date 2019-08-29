#pragma once

#include "MobileObject.h"

class Player : public MobileObject {

private:
	void animate();
	void move(int vel, int& position, int step);
public:
	Player();

	void handleEvent(SDL_Event& e);
	void update();
	void setPosition(int x, int y);
	void setCollisionRect();
	bool isOnGround();
};
