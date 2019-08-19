#pragma once

#include <SDL.h>
#include "Menu.h"
#include "TextureHelper.h"
#include "Game.h"

void Menu::loadTextures() {
	newGameTexture = TextureHelper::textures["menu_new_game_stationary"];
	quitTexture = TextureHelper::textures["menu_quit_stationary"];
	menuSelectorTexture = TextureHelper::textures["menu_selector_stationary"];
	menuTitleTexture = TextureHelper::textures["menu_title_stationary"];
	menuContinueTexture = TextureHelper::textures["menu_continue_stationary"];
}

void Menu::init() {
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
	SDL_Rect targetRect;

	
	targetRect.x = 384;
	targetRect.y = 64;
	targetRect.w = 512;
	targetRect.h = 128;

	SDL_RenderCopy(Game::renderer, menuTitleTexture, NULL, &targetRect);
	
	if (Game::isInProgress)
	{
		targetRect.x = 512;
		targetRect.y = 256;
		targetRect.w = 256;
		targetRect.h = 64;

		SDL_RenderCopy(Game::renderer, menuContinueTexture, NULL, &targetRect);
	}

	targetRect.x = 512;
	targetRect.y = 384;
	targetRect.w = 256;
	targetRect.h = 64;

	SDL_RenderCopy(Game::renderer, newGameTexture, NULL, &targetRect);

	targetRect.x = 512;
	targetRect.y = 512;
	targetRect.w = 256;
	targetRect.h = 64;

	SDL_RenderCopy(Game::renderer, quitTexture, NULL, &targetRect);

	targetRect.x = 384;
	targetRect.w = 64;
	targetRect.h = 64;

	if (continueSelected)
	{
		targetRect.y = 256;
	}
	else if (newGameSelected)
	{
		targetRect.y = 384;
	}
	else if (quitSelected)
	{
		targetRect.y = 512;
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
				Game::showMenu = false;
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

void Menu::clear() {

}