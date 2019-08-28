#pragma once

#include <string>
#include "CollidingObject.h"

class Tile : public CollidingObject {

public:
	void setCollisionRect();
	void update();
	std::string type;

	Tile(int x, int y, std::string ap, std::string t);
};
