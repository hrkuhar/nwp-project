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
#include "Menu.h"
#include <SDL_ttf.h>

Player* Game::player = nullptr;
Level* Game::level = nullptr;
Menu *menu = nullptr;
SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::font = nullptr;

int Game::frame = 1;
int Game::currentLevel = 0;
int Game::lives = 3;
Uint32 Game::startTime = 0;
Uint32 Game::elapsedTime = 0;
Uint32 Game::pauseStartTime = 0;
bool Game::isRunning;
bool Game::showMenu;
bool Game::isInProgress;
bool Game::gameOver;
int Game::map[3][11][20] = {
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 6, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 5, 0, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 3, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
},
{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 6, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 3, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
},
{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1},
		{1, 0, 1, 1, 1, 2, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
}
};

Game::Game() {
	isRunning = true;
	showMenu = true;
	isInProgress = false;
	gameOver = false;
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

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	font = TTF_OpenFont("assets/main_font.ttf", 28);
	if (font == NULL)
	{
		success = false;
	}

	TextureHelper::loadTextures();

	menu = new Menu();
	menu->init();

	player = new Player(64, 64, "player");
	player->init();

	nextLevel();

	return success;
}

void Game::handleEvent(SDL_Event& e) {
	if (e.type == SDL_QUIT)
	{
		isRunning = false;
	}
	else
	{
		if (showMenu)
		{
			menu->handleEvent(e);
		}
		else {
			player->handleEvent(e);
		}
	}
}

void Game::update() {
	if (lives == 0)
	{
		isInProgress = false;
		showMenu = true;
		gameOver = true;
	}

	if (showMenu)
	{
		menu->update();
	}
	else
	{
		level->update();
		player->update();
	}

	if (isInProgress)
	{
		Uint32 currentTime = SDL_GetTicks();
		elapsedTime = currentTime - Game::startTime;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);

	if (showMenu)
	{
		menu->render();
	}
	else
	{
		level->render();
		player->render();
	}

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

void Game::nextLevel() {
	if (currentLevel > 2)
	{
		isInProgress = false;
		showMenu = true;
		gameOver = true;
	}
	level = new Level();
	level->init(map[currentLevel++]);
}

void Game::newGame() {
	currentLevel = 0;
	lives = 3;
	player = new Player(64, 64, "player");
	player->init();

	nextLevel();
	isInProgress = true;
	showMenu = false;
	gameOver = false;

	startTime = SDL_GetTicks();
	pauseStartTime = 0;
}

void Game::resume() {
	showMenu = false;
	startTime += (SDL_GetTicks() - pauseStartTime);
	pauseStartTime = 0;
}

void Game::displayMenu() {
	showMenu = true;
	if (isInProgress)
	{
		menu->continueSelected = true;
		menu->newGameSelected = false;
		menu->quitSelected = false;

		pauseStartTime = SDL_GetTicks();
	}
}
