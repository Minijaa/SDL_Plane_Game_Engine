#ifndef MEMFUNCSHORTCOMMAND_H
#define MEMFUNCSHORTCOMMAND_H
#include "ShortCommand.h"

namespace planeGameEngine {

	template <typename T>
	class MemFuncShortCommand : public ShortCommand
	{
	public:
		void action(SDL_Event event) {
			if (event.key.keysym.sym == key) {
				(object->*func)();
			}
		}
		static MemFuncShortCommand* getInstance(char k, T* obj, void(T::*f)()) {
			return new MemFuncShortCommand(k, obj, f);
		}
		MemFuncShortCommand(const MemFuncShortCommand&) = delete;
		const MemFuncShortCommand& operator=(const MemFuncShortCommand&) = delete;

	protected:
		MemFuncShortCommand(char k, T* obj, void(T::*f)()) : ShortCommand(k), object(obj), func(f) {}

	private:
		T* object;
		void (T::*func)();
	};
}
#endif 