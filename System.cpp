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
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
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

	void System::addSfx(std::string name, std::string& path)
	{
		musicAndSounds[name] = Mix_LoadWAV(path.c_str());
	}
	int System::playSfx(int channel, std::string name, int loops)
	{
		int actualChannel = Mix_PlayChannel(channel, musicAndSounds[name], loops);
		if (actualChannel == -1) {
			throw std::runtime_error("Error loading sfx");
		}
		return actualChannel;
	}


	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		if (!musicAndSounds.empty()) {
			for (auto iter = musicAndSounds.begin(); iter != musicAndSounds.end(); iter++) {
				Mix_FreeChunk(iter->second);
			}
		}
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	FilePaths path;
	System sys;
} //ns
