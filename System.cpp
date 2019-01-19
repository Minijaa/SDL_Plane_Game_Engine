#include "System.h"
#include <stdexcept>
#include <iostream>
using namespace std;
namespace planeGameEngine {

	System::System()
	{
		srand(NULL);
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			cerr << "SDL_Init-error: " << SDL_GetError() << endl;
			exit(-1);
		}
		window = SDL_CreateWindow("Plane Game", 100, 100, XRESOLUTION, YRESOLUTION, 0);
		if (window == nullptr) {
			cerr << "Error: " << SDL_GetError() << endl;
			SDL_Quit();
			exit(-1);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer == nullptr) {
			cerr << "Error: " << SDL_GetError() << endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(-1);
		}
		TTF_Init();
		font = TTF_OpenFont(path.f_GilsansFont.c_str(), 36);
		if (font == nullptr) {
			throw std::runtime_error("Font not found");
		}
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	}

	SDL_Renderer* System::getRenderer() const {
		return renderer;
	}
	TTF_Font* System::getFont() const {
		return font;
	}

	int System::generateRandomNumber(int maxRandomNr, int minRandomNr) const {
		int result = 0;
		result = rand() % maxRandomNr + minRandomNr;
		return result;
	}

	void System::addSfx(std::string name, std::string& path)
	{
		Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
		if (sound == nullptr) {
			throw std::runtime_error(Mix_GetError());
		}
		sounds[name] = sound;
	}
	int System::playSfx(int channel, std::string name, int loops)
	{
		int actualChannel = Mix_PlayChannel(channel, sounds[name], loops);
		if (actualChannel == -1) {
			throw std::runtime_error(Mix_GetError());
		}
		return actualChannel;
	}
	void System::addMusic(std::string name, std::string& path)
	{
		Mix_Music* music = Mix_LoadMUS(path.c_str());
		if (music == nullptr) {
			throw std::runtime_error(Mix_GetError());
		}
		tunes[name] = music;
	}
	void System::playMusic(std::string name, int loops, int fade)
	{
		if (Mix_PlayMusic(tunes[name], -1) == -1) {
			throw std::runtime_error(Mix_GetError());
		}
	}

	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		if (!sounds.empty()) {
			for (auto iter = sounds.begin(); iter != sounds.end(); iter++) {
				Mix_FreeChunk(iter->second);
			}
		}
		if (!tunes.empty()) {
			for (auto iter = tunes.begin(); iter != tunes.end(); iter++) {
				Mix_FreeMusic(iter->second);
			}
		}
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	FilePaths path;
	System sys;
} //ns
