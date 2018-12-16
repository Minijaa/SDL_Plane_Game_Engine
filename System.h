#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "FilePaths.h"
#include <SDL_mixer.h>
#include <unordered_map>

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
		//void addSfx(std::string name, std::string path);

	private:
		const int XRESOLUTION = 1280;
		const int YRESOLUTION = 720;
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Mix_Chunk* music;
		//Lägg till dessa i en vector eller unordered_map istället med metod addSfx(string, )
		Mix_Chunk* bulletSound;
		Mix_Chunk* hitSound;
		Mix_Chunk* exploadSound;
		Mix_Chunk* missileSound;
		//unordered_map<Mix_Chunk*> musicAndSounds; //FORTSÄTT HÄR
	};

	extern System sys;
	

} //ns
#endif