#pragma once

#include <SDL.h>
#include "CollidingObject.h"
#include <string>

class MobileObject : public CollidingObject {
protected:
	int velocity;
	int velocityX;
	int velocityY;
	virtual bool isOnGround();
	bool isTouchingCeiling();
	void applyGravity();
	void checkBoundries();
	SDL_Texture* jumpingTexture;
	SDL_Texture* moveTextures[4];
public:
	MobileObject(int x, int y, std::string ap, int vel, int velX, int velY);
	void setTextures();
};

