#ifndef FUNCSHORTCOMMAND_H
#define FUNCSHORTCOMMAND_H
#include "ShortCommand.h"

namespace planeGameEngine {

	class FuncShortCommand : public ShortCommand
	{
	public:
		FuncShortCommand(char k, void(*f)()) :ShortCommand(k), func(f) {}
		static FuncShortCommand* getInstance(char k, void(*f)()) {
			return new FuncShortCommand(k, f);
		}
		void action(SDL_Event event) {
			if (event.key.keysym.sym == key) {
				func();
			}
		}
	private:
		void(*func)();
	};
}
#endif
