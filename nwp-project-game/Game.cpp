#include <SDL_image.h>
#include "Game.h"
#include "Player.h"
#include "TextureHelper.h"
#include "TextHelper.h"
#include "Menu.h"
#include <fstream>
#include <sstream>

SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::font = nullptr;

Player* Game::player = nullptr;
Level* Game::level = nullptr;
Menu *menu = nullptr;

int Game::currentLevel = 0;
int Game::frame = 1;

int Game::lives = 3;

Uint32 Game::startTime = 0;
Uint32 Game::elapsedTime = 0;
Uint32 Game::pauseStartTime = 0;

bool Game::isRunning;
bool Game::showMenu;
bool Game::isInProgress;
bool Game::gameOver;

std::vector<std::string> Game::levelMaps;

Game::Game() {
	isRunning = true;
	showMenu = true;
	isInProgress = false;
	gameOver = false;
}

bool Game::init() {
	bool success = true;

	TextHelper::loadCSV();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		window = SDL_CreateWindow(TextHelper::values["game_title"].c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	player = new Player();

	loadLevelMaps();

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

void Game::nextLevel() {
	if (currentLevel > LEVEL_COUNT)
	{
		isInProgress = false;
		showMenu = true;
		gameOver = true;
	}

	delete level;

	level = new Level(levelMaps.at(currentLevel));
	++currentLevel;
}

void Game::newGame() {
	currentLevel = 0;
	lives = 3;

	delete player;
	player = new Player();

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

Game::~Game() {
	TextureHelper::clear();

	delete player;
	player = NULL;
	delete menu;
	menu = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Game::loadLevelMaps() {
	std::string line;
	std::ifstream levelsFile("assets/levels.txt");
	if (levelsFile.is_open())
	{
		while (getline(levelsFile, line, '/'))
		{
			std::string level = line;

			std::string charsToTrim = "\n";

			level = level.erase(0, level.find_first_not_of(charsToTrim));
			level = level.erase(level.find_last_not_of(charsToTrim) + 1);

			levelMaps.push_back(level);
		}
		levelsFile.close();
	}
}