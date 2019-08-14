#include <SDL.h>
#include <stdio.h>

class Game {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
public:
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