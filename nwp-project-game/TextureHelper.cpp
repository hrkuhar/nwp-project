#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "TextureHelper.h"
#include "Game.h"
#include <map>

std::map<std::string, SDL_Texture*> TextureHelper::textures;

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

void TextureHelper::loadTextures() {
	textures["player_stationary"] = loadTexture(Game::renderer, "assets/player_stationary.png");
	textures["player_jump"] = loadTexture(Game::renderer, "assets/player_jump.png");
	textures["player_move_1"] = loadTexture(Game::renderer, "assets/player_move_1.png");
	textures["player_move_2"] = loadTexture(Game::renderer, "assets/player_move_2.png");
	textures["player_move_3"] = loadTexture(Game::renderer, "assets/player_move_3.png");
	textures["player_move_4"] = loadTexture(Game::renderer, "assets/player_move_4.png");

	textures["enemy_move_1"] = loadTexture(Game::renderer, "assets/enemy_move_1.png");
	textures["enemy_move_2"] = loadTexture(Game::renderer, "assets/enemy_move_2.png");
	textures["enemy_move_3"] = loadTexture(Game::renderer, "assets/enemy_move_3.png");
	textures["enemy_move_4"] = loadTexture(Game::renderer, "assets/enemy_move_4.png");

	textures["brick_stationary"] = loadTexture(Game::renderer, "assets/brick_stationary.png");

	textures["spike_stationary"] = loadTexture(Game::renderer, "assets/spike_stationary.png");

	textures["level_start_stationary"] = loadTexture(Game::renderer, "assets/level_start_stationary.png");

	textures["level_end_stationary"] = loadTexture(Game::renderer, "assets/level_end_stationary.png");

}

void TextureHelper::clear() {
	//ToDo
}