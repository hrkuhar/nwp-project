#pragma once
#include <SDL.h>
#include <string>

class GameObject {
protected:
	int width;
	int height;

	SDL_Texture* texture;
	SDL_Texture* standingTexture;

	SDL_RendererFlip flipTextures = SDL_FLIP_NONE;

	int positionX;
	int positionY;
	std::string assetsPrefix;

	void setTextures();
public:
	GameObject(int x, int y, std::string ap);

	void render();
	virtual void update() = 0;
};
