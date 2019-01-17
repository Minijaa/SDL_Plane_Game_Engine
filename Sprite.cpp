#include "Sprite.h"
#include <SDL.h>
#include "System.h"

namespace planeGameEngine {


	Sprite::Sprite(int x, int y, int w, int h, bool isInteractable) :rect{ x, y, w, h },interactable(isInteractable)
	{
		
	}

	void Sprite::setWH(int w, int h) {
		rect.w = w;
		rect.h = h;
	}

	void Sprite::setXY(int x, int y) {
		rect.x = x;
		rect.y = y;
	}
	
}
