#include "Sprite.h"
#include <SDL.h>
#include "System.h"

namespace planeGameEngine {

	Sprite::Sprite(int x, int y, int w, int h, bool isInteractable) :rect{ x, y, w, h },interactable(isInteractable), defaultPosX(x), defaultPosY(y) {}

	void Sprite::setWH(int w, int h) {
		rect.w = w;
		rect.h = h;
	}

	// If rectangle based collission is detected between two sprites, loop through each pixel of the intersect rectangle
	// and forward pixel position to function "collidableColor" in both Sprites.
	bool Sprite::collisionDetected(Sprite* other) {
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

	// check argument pixel position for color and returns true if color isn't fully transparent
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
