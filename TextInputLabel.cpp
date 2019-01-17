#include "TextInputLabel.h"
#include <iostream>

namespace planeGameEngine {
	void TextInputLabel::input(const SDL_Event & event)
	{
		setText(getText() + event.text.text);
	}
	void TextInputLabel::keyDown(const SDL_Event& event) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_TEXTINPUT) {
			if (event.key.keysym.sym == SDLK_RETURN) {
				//SDL_StopTextInput();
				perform();
				setText("");
			}
			else if (event.key.keysym.sym == SDLK_BACKSPACE && getText().length() > 0) {
				setText(getText().substr(0, getText().length() -1));
			}
		}
	}
	TextInputLabel::~TextInputLabel()
	{
	}
	TextInputLabel* TextInputLabel::getInstance(int x, int y, const std::string & txt, SDL_Color col)
	{
		return new TextInputLabel(x, y, txt, col);
	}
	void TextInputLabel::stopTextInput()
	{
		SDL_StopTextInput();
	}
	void TextInputLabel::startTextInput()
	{
		SDL_SetTextInputRect(&getRect());
	}
	TextInputLabel::TextInputLabel(int x, int y, const std::string & txt, SDL_Color col): Label(x, y, txt, col)
	{
		makeTexture();
		startTextInput();
	}
}
