#pragma once

class Menu {
private:
	SDL_Texture* newGameTexture;
	SDL_Texture* quitTexture;
	SDL_Texture* menuSelectorTexture;
	SDL_Texture* menuTitleTexture;
	SDL_Texture* menuContinueTexture;
public:
	bool newGameSelected;
	bool quitSelected;
	bool continueSelected;

	void init();
	void loadTextures();
	void update();
	void render();
	void clear();
	void handleEvent(SDL_Event& e);
};