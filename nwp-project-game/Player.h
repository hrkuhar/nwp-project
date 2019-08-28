#pragma once

#include "MobileObject.h"

class Player : public MobileObject {

private:
	void animate();
public:
	void init();
	void handleEvent(SDL_Event& e);
	void update();
	void setPosition(int x, int y);
	void setCollisionRect();
	bool isOnGround();

	Player(int x, int y, std::string ap);
};
