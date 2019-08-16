#pragma once

#include <SDL.h>
#include "CollidingObject.h"
#include "Tile.h"
#include "Game.h"

Tile::Tile(int x, int y, std::string ap) : CollidingObject(x, y, ap) {
	texture = standingTexture;
}

void Tile::setCollisionRect() {
	collisionRect->w = WIDTH;
	collisionRect->h = HEIGHT;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}

void Tile::update() {

}