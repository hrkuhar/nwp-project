#include "Tile.h"

Tile::Tile(int x, int y, std::string ap, std::string t) : CollidingObject(x, y, ap) {
	texture = standingTexture;
	type = t;
}

void Tile::setCollisionRect() {
	collisionRect->w = width;
	collisionRect->h = height;
	collisionRect->x = positionX;
	collisionRect->y = positionY;
}

void Tile::update() {

}