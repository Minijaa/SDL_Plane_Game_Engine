#include "System.h"
#include <stdexcept>

namespace planeGameEngine {

	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Plane Game", 100, 100, XRESOLUTION, YRESOLUTION, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		TTF_Init();
		font = TTF_OpenFont("Fonts/BAUHS93.TTF", 24);
		if (font == nullptr) {
			throw std::runtime_error("Font not found");
		}
	}
	SDL_Renderer* System::getRenderer()const {
		return renderer;
	}
	TTF_Font* System::getFont() const {
		return font;
	}

	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	System system;
} //ns
