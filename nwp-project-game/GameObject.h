#pragma once
#include <SDL.h>
#include <string>

class GameObject {
protected:
	SDL_Texture* texture;

	SDL_Texture* standingTexture;

	SDL_RendererFlip flipTextures = SDL_FLIP_NONE;
	const int WIDTH = 64;
	const int HEIGHT = 64;
	int positionX;
	int positionY;
	std::string assetsPrefix;
	void setTextures();
public:
	virtual void update() = 0;
	void render();
	GameObject(int x, int y, std::string ap);
};
