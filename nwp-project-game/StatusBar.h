#pragma once

class StatusBar {
private:
	SDL_Texture* lifeTexture;
public:
	StatusBar();

	void loadTextures();
	void render();
};