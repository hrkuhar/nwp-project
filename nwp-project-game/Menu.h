#pragma once

class Menu {
private:
	SDL_Texture* newGameTexture;
	SDL_Texture* quitTexture;
	SDL_Texture* menuSelectorTexture;
	SDL_Texture* menuTitleTexture;
	SDL_Texture* menuContinueTexture;
public:
	Menu();

	bool newGameSelected;
	bool quitSelected;
	bool continueSelected;

	void loadTextures();
	void update();
	void render();
	void handleEvent(SDL_Event& e);
};