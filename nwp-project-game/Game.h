#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"

class Game {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;

	static int map[2][12][20];

	static int currentLevel;
public:
	static SDL_Renderer* renderer;
	static int frame;
	static Player* player;

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static void nextLevel();

	Game();
	~Game();
	bool isRunning;

	bool init();
	void update();
	void render();
	void clear();
	void handleEvent(SDL_Event& e);
};