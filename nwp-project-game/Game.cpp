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

Player *player = nullptr;
Level *level = nullptr;
Enemy *enemy1 = nullptr;
Enemy *enemy2 = nullptr;
SDL_Renderer* Game::renderer = nullptr;


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

	level = new Level();
	level->init();

	enemy1 = new Enemy(level, 150, 150);
	enemy1->init();

	enemy2 = new Enemy(level, 500, 500);
	enemy2->init();

	enemies.push_back(enemy1);
	enemies.push_back(enemy2);

	player = new Player(level, enemies);
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

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = i + 1; j < enemies.size(); j++)
		{
			if (CollisionHelper::checkCollision(enemies[i]->collisionRect, enemies[j]->collisionRect))
			{
				enemies[i]->changeDirection();
				enemies[j]->changeDirection();
			}
		}
	}

	player->update();
}

void Game::render() {
	SDL_RenderClear(renderer);

	level->render();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render();
	}	
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
