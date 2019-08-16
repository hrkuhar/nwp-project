#pragma once

#include <SDL.h>
#include <string>
#include "Collider.h"
#include "GameObject.h"

class Tile : public GameObject, public Collider {

public:
	void setCollisionRect();
	void update();

	Tile(int x, int y, SDL_Texture* t);
};
