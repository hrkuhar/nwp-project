#pragma once

#include <SDL.h>
#include "CollidingObject.h"
#include "Tile.h"
#include "Game.h"

Tile::Tile(int x, int y, SDL_Texture* t) : CollidingObject(x, y) {
	texture = t;
}

void Tile::setCollisionRect() {
	collisionRect->w = WIDTH;
	collisionRect->h = HEIGHT;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}

void Tile::update() {

}