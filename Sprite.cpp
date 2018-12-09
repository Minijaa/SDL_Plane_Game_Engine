#include "Sprite.h"
#include <SDL.h>
#include "System.h"

namespace planeGameEngine {


	Sprite::Sprite(int x, int y, int w, int h) :rect{ x, y, w, h }
	{
	}

	void Sprite::setWH(int w, int h) {
		rect.w = w;
		rect.h = h;
	}
}
