#pragma once

#include <SDL.h>
#include "Collider.h"
#include "Tile.h"

void Tile::setCollisionRect() {
	collisionRect->w = width;
	collisionRect->h = height;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}