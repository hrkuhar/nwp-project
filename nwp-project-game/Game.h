#pragma once

#include "Player.h"
#include "Level.h"
#include <SDL_ttf.h>

class Game {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
public:
	Game();
	~Game();
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;
	static const int LEVEL_COUNT = 8;

	static int map[LEVEL_COUNT][11][20];

	static SDL_Renderer* renderer;
	static TTF_Font *font;
	static Player* player;
	static Level* level;

	static int currentLevel;
	static int lives;

	static int frame;
	static Uint32 startTime;
	static Uint32 pauseStartTime;
	static Uint32 elapsedTime;

	static bool isRunning;
	static bool showMenu;
	static bool isInProgress;
	static bool gameOver;

	static void nextLevel();
	static void newGame();
	static void resume();
	static void displayMenu();

	bool init();
	void update();
	void render();
	void handleEvent(SDL_Event& e);
};