#ifndef TEXTINPUTLABEL_H
#define TEXTINPUTLABEL_H
#include <string>
#include <SDL.h>
#include "Label.h"

namespace planeGameEngine {

	class TextInputLabel : public Label
	{
	public:
		void input(const SDL_Event& event);
		void keyDown(const SDL_Event& event);
		virtual void perform() {}
		~TextInputLabel();
		static TextInputLabel* getInstance(int x, int y, const std::string& txt, SDL_Color col);
		void startTextInput();
		void stopTextInput();
	protected:
		TextInputLabel(int x, int y, const std::string& txt, SDL_Color col);
	};
}
#endif