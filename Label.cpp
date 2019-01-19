#include "Label.h"
#include "SDL_ttf.h"
#include "System.h"
#include <iostream>
namespace planeGameEngine {
	Label* Label::getInstance(int x, int y, const std::string& txt, SDL_Color col) {
		return new Label(x, y, txt, col);
	}
	void Label::setText(const std::string& txt) {
		text = txt;
		makeTexture();
	}
	void Label::draw()  {
		SDL_RenderCopy(sys.getRenderer(), getTexture(), NULL, &getRect());
	}
	Label::~Label()
	{
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(getSurf());
		}
	}
	Label::Label(int x, int y, const std::string & txt, SDL_Color col) : Sprite(x, y, 0, 0), text(txt), color(col) {
		makeTexture();
	}
	void Label::makeTexture() {
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
		}
		SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), color);
		if (surf == nullptr) {
			surf = TTF_RenderText_Solid(sys.getFont(), "_", color);
			setSurf(surf);
		}
		texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surf);
		setWH(surf->w, surf->h);
	}
}
