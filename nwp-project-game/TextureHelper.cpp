#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "TextureHelper.h"

SDL_Texture* TextureHelper::loadTexture(SDL_Renderer* renderer, std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}