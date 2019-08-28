#pragma once

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