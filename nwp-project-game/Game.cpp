#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Game.h"
#include "Player.h";

Player *player = nullptr;

Game::Game() {
	isRunning = true;
}

Game::~Game() {

}

bool Game::init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("NWP game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					success = false;
				}
			}
		}
	}

	player = new Player();
	player->init(renderer);

	return success;
}

void Game::handleEvent(SDL_Event& e) {

	if (e.type == SDL_QUIT)
	{
		isRunning = false;
	}
	else
	{
		player->handleEvent(e);
	}
}

void Game::update() {
	player->update(screenSurface);
}

void Game::render() {
	SDL_RenderClear(renderer);

	player->render();

	SDL_RenderPresent(renderer);
}

void Game::clear() {
	player->clear();

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
