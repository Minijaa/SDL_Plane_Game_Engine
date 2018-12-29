#ifndef LABEL_H
#define LABEL_H
#include "Sprite.h"
#include <SDL.h>
#include <string>

namespace planeGameEngine {

	class Label : public Sprite
	{

	public:
		static Label* getInstance(int x, int y, const std::string& txt, SDL_Color col);
		void setText(const std::string& txt);
		std::string getText() const;
		void draw() const;
		~Label();
		Label(const Label&) = delete;
		const Label& operator=(const Label&) = delete;

	protected:
		Label(int x, int y, const std::string& txt, SDL_Color col);
		SDL_Texture* getTexture() const { return texture; }
		void makeTexture();

	private:
		std::string text;
		SDL_Texture* texture = nullptr;
		SDL_Color color;
	};

}
#endif
