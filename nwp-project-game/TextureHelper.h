#pragma once

#include <map>

class TextureHelper {
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);
	static SDL_Texture* loadFromRenderedText(std::string textureText, SDL_Color textColor);


	static std::map<std::string, SDL_Texture*> textures;

	static void loadTextures();
	static void clear();
};