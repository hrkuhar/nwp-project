#pragma once

#include "MobileObject.h"

class Enemy : public MobileObject {

private:
	int jumpHeight;

	void animate();
	void changeDirection();
public:
	Enemy(int posX, int posY, std::string ap, int jump);

	void update();
};
