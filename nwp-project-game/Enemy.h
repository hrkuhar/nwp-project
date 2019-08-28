#pragma once

#include "MobileObject.h"

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
