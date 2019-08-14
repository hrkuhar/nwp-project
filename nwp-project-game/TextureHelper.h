#pragma once

#include <SDL.h>
#include <string>

class TextureHelper {
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);
};