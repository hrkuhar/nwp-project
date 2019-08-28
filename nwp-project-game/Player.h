#pragma once

#include "MobileObject.h"

class Player : public MobileObject {

private:
	void animate();
public:
	Player(int x, int y, std::string ap);

	void init();
	void handleEvent(SDL_Event& e);
	void update();
	void setPosition(int x, int y);
	void setCollisionRect();
	bool isOnGround();
};
