#pragma once
#include <SDL.h>

class GameObject {
protected:
	SDL_Texture* texture;
	SDL_RendererFlip flipTextures = SDL_FLIP_NONE;
	const int WIDTH = 64;
	const int HEIGHT = 64;
	int positionX;
	int positionY;
public:
	virtual void update() = 0;
	void render();
	GameObject(int x, int y);
};
