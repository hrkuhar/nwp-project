#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Level.h"

class Game {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;

	static int map[3][11][20];

	static int currentLevel;
public:
	static SDL_Renderer* renderer;
	static int frame;
	static Player* player;
	static Level* level;
	static int lives;

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static void nextLevel();
	static void newGame();
	static void displayMenu();

	Game();
	~Game();
	static bool isRunning;
	static bool showMenu;
	static bool isInProgress;

	bool init();
	void update();
	void render();
	void clear();
	void handleEvent(SDL_Event& e);
};