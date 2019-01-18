#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Sprite.h"
#include <SDL.h>
#include <string>

namespace planeGameEngine {

	class Background :public Sprite
	{
	public:
		static Background* getInstance(std::string& imagePath);
		void draw();
		Background(const Background&) = delete;
		const Background& operator=(const Background&) = delete;

		~Background();
	protected:
		Background(std::string& imagePath);

	private:
		SDL_Texture* bgTexture;
	};

}
#endif
