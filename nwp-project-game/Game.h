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
public:
	static SDL_Renderer* renderer;
	static int frame;
	static Player* player;

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	Game();
	~Game();
	bool isRunning;

	bool init();
	void update();
	void render();
	void clear();
	void handleEvent(SDL_Event& e);
};