#include <SDL.h>
#include "Menu.h"
#include "TextureHelper.h"
#include "Game.h"
#include "TimeHelper.h"
#include "TextHelper.h"

void Menu::loadTextures() {
	newGameTexture = TextureHelper::textures["menu_new_game_stationary"];
	quitTexture = TextureHelper::textures["menu_quit_stationary"];
	menuSelectorTexture = TextureHelper::textures["menu_selector_stationary"];
	menuTitleTexture = TextureHelper::textures["menu_title_stationary"];
	menuContinueTexture = TextureHelper::textures["menu_continue_stationary"];
}

Menu::Menu() {
	loadTextures();
	newGameSelected = true;
	quitSelected = false;
	continueSelected = false;
}

void Menu::update() {
	if (!Game::isInProgress && continueSelected)
	{
		continueSelected = false;
		newGameSelected = true;
		quitSelected = false;
	}
}

void Menu::render() {

	int tileSize = Game::SCREEN_WIDTH / 20;

	SDL_Rect targetRect;

	targetRect.x = 6 * tileSize;
	targetRect.y = tileSize;
	targetRect.w = 8 * tileSize;
	targetRect.h = 2 * tileSize;

	SDL_RenderCopy(Game::renderer, menuTitleTexture, NULL, &targetRect);
	
	if (Game::isInProgress)
	{
		targetRect.x = 8 * tileSize;
		targetRect.y = 4 * tileSize;
		targetRect.w = 4 * tileSize;
		targetRect.h = tileSize;

		SDL_RenderCopy(Game::renderer, menuContinueTexture, NULL, &targetRect);
	}
	else if (Game::gameOver)
	{
		targetRect.x = 2 * tileSize;
		targetRect.y = 4 * tileSize;
		targetRect.w = 16 * tileSize;
		targetRect.h = tileSize;

		std::string message;

		if (Game::currentLevel > Game::LEVEL_COUNT)
		{
			message = TextHelper::values["message_game_finished"];
		}
		else {
			message = TextHelper::values["message_level_reached"] + std::to_string(Game::currentLevel) + "!";
		}

		SDL_Texture* texture = TextureHelper::loadFromRenderedText(message + TextHelper::values["message_game_time"] + TimeHelper::millisToString(Game::elapsedTime), { 0, 0, 0 });
		SDL_RenderCopy(Game::renderer, texture , NULL, &targetRect);
		SDL_DestroyTexture(texture);
	}

	targetRect.x = 8 *tileSize;
	targetRect.y = 6 * tileSize;
	targetRect.w = 4 * tileSize;
	targetRect.h = tileSize;

	SDL_RenderCopy(Game::renderer, newGameTexture, NULL, &targetRect);

	targetRect.x = 8 * tileSize;
	targetRect.y = 8 * tileSize;
	targetRect.w = 4 * tileSize;
	targetRect.h = tileSize;

	SDL_RenderCopy(Game::renderer, quitTexture, NULL, &targetRect);

	targetRect.x = 6 * tileSize;
	targetRect.w = tileSize;
	targetRect.h = tileSize;

	if (continueSelected)
	{
		targetRect.y = 4 * tileSize;
	}
	else if (newGameSelected)
	{
		targetRect.y = 6 * tileSize;
	}
	else if (quitSelected)
	{
		targetRect.y = 8 * tileSize;
	}

	SDL_RenderCopy(Game::renderer, menuSelectorTexture, NULL, &targetRect);
}

void Menu::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (quitSelected)
			{
				continueSelected = false;
				newGameSelected = true;
				quitSelected = false;
			}
			else if (newGameSelected && Game::isInProgress)
			{
				continueSelected = true;
				newGameSelected = false;
				quitSelected = false;
			}
			break;
		case SDLK_DOWN:
			if (newGameSelected)
			{
				continueSelected = false;
				newGameSelected = false;
				quitSelected = true;
			}
			else if (continueSelected)
			{
				continueSelected = false;
				newGameSelected = true;
				quitSelected = false;
			}
			break;
		case SDLK_RETURN:
			if (continueSelected)
			{
				Game::resume();
			}
			else if (newGameSelected)
			{
				Game::newGame();
			}
			else if (quitSelected)
			{
				Game::isRunning = false;
			}
			break;
		}
	}
}