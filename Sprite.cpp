#include "Sprite.h"
#include <SDL.h>
#include "System.h"

namespace planeGameEngine {

	Sprite::Sprite(int x, int y, int w, int h, bool isInteractable) :rect{ x, y, w, h },interactable(isInteractable)
	{}

	void Sprite::setWH(int w, int h) {
		rect.w = w;
		rect.h = h;
	}

	bool Sprite::collisionDetected(Sprite* other) 
	{
		SDL_Rect intersect;
		if (SDL_IntersectRect(&getRect(), &other->getRect(), &intersect)) {
			for (int x = 0; x < intersect.w; x++) {
				for (int y = 0; y < intersect.h; y++) {
					if (collidableColor(intersect.x + x, intersect.y + y) && other->collidableColor(intersect.x + x, intersect.y + y)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Sprite::collidableColor(int intersectX, int intersectY) 
	{
		int x = intersectX - getX();
		int y = intersectY - getY();
		SDL_LockSurface(surf);
		Uint32* pixels = static_cast<Uint32*>(surf->pixels);
		Uint32 pixel = pixels[y*surf->w + x];
		SDL_UnlockSurface(surf);
		Uint32 alpha = pixel & surf->format->Amask;
		alpha = alpha >> surf->format->Ashift;
		return alpha > 0;
	}

	void Sprite::setXY(int x, int y) {
		rect.x = x;
		rect.y = y;
	}
	
}
