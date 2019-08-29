#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	if (game->init())
	{
		SDL_Event e;

		while (game->isRunning)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				game->handleEvent(e);
			}

			game->update();
			game->render();
		}

		delete game;
		game = NULL;

		return 0;
	}
	else
	{
		return 1;
	}
}