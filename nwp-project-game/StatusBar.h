#pragma once

#include <SDL.h>

class StatusBar {
private:
	SDL_Texture* lifeTexture;
public:
	void init();
	void loadTextures();
	void update();
	void render();
	void clear();
};