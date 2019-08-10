#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	game->init();

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

	game->clear();

	return 0;
}