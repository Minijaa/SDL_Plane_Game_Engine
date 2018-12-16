#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "FilePaths.h"

namespace planeGameEngine {

	class System
	{
	public:
		System();
		~System();
		SDL_Renderer* getRenderer() const;
		TTF_Font* getFont() const;
		int getXResolution() const { return XRESOLUTION; }
		int getYResolution() const { return YRESOLUTION; }
		int generateRandomNumber(int maxRandomNr, int minRandomNr);

	private:
		const int XRESOLUTION = 1280;
		const int YRESOLUTION = 720;
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
	};

	extern System sys;
	

} //ns
#endif