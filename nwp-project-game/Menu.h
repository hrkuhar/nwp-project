#pragma once

#include <SDL.h>

class Menu {
private:
	SDL_Texture* newGameTexture;
	SDL_Texture* quitTexture;
	SDL_Texture* menuSelectorTexture;
	SDL_Texture* menuTitleTexture;
	SDL_Texture* menuContinueTexture;

	
public:
	void init();
	void loadTextures();
	void update();
	void render();
	void clear();
	void handleEvent(SDL_Event& e);

	bool newGameSelected;
	bool quitSelected;
	bool continueSelected;
};