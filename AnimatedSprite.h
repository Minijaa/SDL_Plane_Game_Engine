#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "Sprite.h"
#include <string>
#include "MovingSprite.h"

namespace planeGameEngine {

	class AnimatedSprite : virtual public Sprite
	{
	public:
		static AnimatedSprite* getInstance(int x, int y, int w, int h, std::string& imagePath);
		~AnimatedSprite();
		void draw() const;
		
	protected:
		AnimatedSprite(int x, int y, int w, int h, std::string& imagePath);
	};

}
#endif