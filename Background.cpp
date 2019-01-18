#include "Background.h"
#include <SDL_image.h>
#include "System.h"
#include <SDL.h>
#include <iostream>

namespace planeGameEngine {


	Background::Background(std::string& imagePath) :Sprite(0, 0, NULL, NULL)
	{
		bgTexture = IMG_LoadTexture(sys.getRenderer(), imagePath.c_str());
		if (bgTexture == nullptr) {
			throw std::runtime_error("Background image not found");
		}
	}

	Background* Background::getInstance(std::string& imagePath)
	{
		return new Background(imagePath);
	}

	void Background::draw() 
	{
		SDL_RenderCopy(sys.getRenderer(), bgTexture, NULL, NULL);
	}

	Background::~Background()
	{
		if (bgTexture != nullptr) {
			SDL_DestroyTexture(bgTexture);
		}
	}
}
