#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Level.h"
#include <SDL_ttf.h>

class Game {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;

	static int map[8][11][20];

public:
	static int currentLevel;
	static SDL_Renderer* renderer;
	static int frame;
	static Player* player;
	static Level* level;
	static int lives;
	static Uint32 startTime;
	static Uint32 pauseStartTime;
	static Uint32 elapsedTime;

	static TTF_Font *font;

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static void nextLevel();
	static void newGame();
	static void resume();
	static void displayMenu();

	Game();
	~Game();
	static bool isRunning;
	static bool showMenu;
	static bool isInProgress;
	static bool gameOver;

	bool init();
	void update();
	void render();
	void clear();
	void handleEvent(SDL_Event& e);
};