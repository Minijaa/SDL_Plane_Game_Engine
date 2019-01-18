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
		void addSfx(std::string name, std::string& path);
		int playSfx(int channel, std::string name, int loops);
		void addMusic(std::string name, std::string& path);
		void playMusic(std::string name, int loops, int fade);
		int audioChannel1, audioChannel2;
		float getGravity() const { return GRAVITY; }

	private:
		const int XRESOLUTION = 1280;
		const int YRESOLUTION = 720;
		const float GRAVITY = 0.15f;
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		std::unordered_map<std::string, Mix_Music*> tunes;
		std::unordered_map<std::string, Mix_Chunk*> sounds;
	};

	extern System sys;
	

} //ns
#endif