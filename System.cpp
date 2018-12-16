#include "System.h"
#include <stdexcept>

namespace planeGameEngine {

	System::System()
	{
		srand(NULL);
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Plane Game", 100, 100, XRESOLUTION, YRESOLUTION, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		TTF_Init();
		font = TTF_OpenFont(path.f_BauhausFont.c_str(), 24);
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

	int System::generateRandomNumber(int maxRandomNr, int minRandomNr) {
		int result = 0;
		result = rand() % maxRandomNr + minRandomNr;
		return result;
	}

	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	System sys;
	FilePaths path;
} //ns
