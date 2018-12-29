#ifndef SHORTCOMMAND_H
#define SHORTCOMMAND_H
#include <SDL.h>

namespace planeGameEngine {

	class ShortCommand
	{
	protected:
		char key;
	public:
		ShortCommand(char k) :key(k) {}
		virtual void action(SDL_Event event) = 0;
		ShortCommand(const ShortCommand&) = delete;
		const ShortCommand& operator=(const ShortCommand&) = delete;
	};
}
#endif 