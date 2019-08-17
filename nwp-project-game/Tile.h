#pragma once

#include <SDL.h>
#include <string>
#include "CollidingObject.h"
#include "GameObject.h"

class Tile : public CollidingObject {

public:
	void setCollisionRect();
	void update();
	std::string type;

	Tile(int x, int y, std::string ap, std::string t);
};
