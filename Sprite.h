#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>

namespace planeGameEngine {

	class Sprite
	{
	public:
		//Inline function
		SDL_Rect getRect() const {
			return rect;
		}

		//Subclasses can override these functions
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		virtual void keyDown(const SDL_Event& event) {}
		virtual void keyUp(const SDL_Event& event) {}

		//Subclasses must override this function
		virtual void draw() const = 0;

		//Subclasses can override desctructor
		virtual ~Sprite() {}

		//Forbids copy constructor and assignment operator in order to prevent using value semantics
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;

	protected:
		Sprite(int x, int y, int w, int h);
		void setWH(int w, int h);

	private:
		SDL_Rect rect;
	};

}
#endif