#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>

class Player {

private:
	SDL_Texture* currentTexture;

	SDL_Texture* moveRightTextures[4];
	SDL_Texture* standingTexture;
	SDL_Texture* jumpingTexture;

	const int width = 64;
	const int height = 64;
	const int velocity = 4;

	int positionX = 600;
	int positionY = 300;

	int velocityX = 0;
	int velocityY = 0;

	int frame = 1;

	SDL_Renderer* renderer = NULL;
	SDL_RendererFlip flipTextures = SDL_FLIP_NONE;

	bool isOnGround();
	void applyGravity();
	void checkBoundaries();
	void loadTextures();
	void animate();
public:
	void init(SDL_Renderer* renderer);
	void handleEvent(SDL_Event& e);
	void update(SDL_Surface* screenSurface);
	void render();
	void clear();
};
