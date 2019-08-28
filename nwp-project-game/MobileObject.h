#pragma once

#include "CollidingObject.h"

class MobileObject : public CollidingObject {
protected:
	SDL_Texture* jumpingTexture;
	SDL_Texture* moveTextures[4];

	int velocity;
	int velocityX;
	int velocityY;

	virtual bool isOnGround();
	bool isTouchingCeiling();
	void applyGravity();
	void checkBoundries();
public:
	MobileObject(int x, int y, std::string ap, int vel, int velX, int velY);
	void setTextures();
};

