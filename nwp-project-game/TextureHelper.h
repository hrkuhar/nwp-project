#pragma once

#include <SDL.h>
#include <string>
#include <map>

class TextureHelper {
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);

	static std::map<std::string, SDL_Texture*> textures;

	static void loadTextures();
	static void clear();
};