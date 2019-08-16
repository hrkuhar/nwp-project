#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "Game.h"
#include "Player.h"
#include "CollisionHelper.h"
#include "Level.h"
#include "Enemy.h"
#include <vector>
#include "TextureHelper.h"

Player *player = nullptr;
Level *level = nullptr;
SDL_Renderer* Game::renderer = nullptr;
int Game::frame = 1;

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

	TextureHelper::loadTextures();

	level = new Level();
	level->init();

	player = new Player(70, 70, "player");
	player->init();

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
	level->update();
	player->update();
}

void Game::render() {
	SDL_RenderClear(renderer);

	level->render();
	player->render();

	SDL_RenderPresent(renderer);
	++frame;
}

void Game::clear() {
	TextureHelper::clear();

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
