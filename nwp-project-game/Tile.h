#pragma once

#include <string>
#include "CollidingObject.h"

class Tile : public CollidingObject {
public:
	Tile(int x, int y, std::string ap, std::string t);

	void setCollisionRect();
	std::string type;
	void update();
};
