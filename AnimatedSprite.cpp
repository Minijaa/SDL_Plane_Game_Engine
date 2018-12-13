#include "AnimatedSprite.h"

namespace planeGameEngine {

	AnimatedSprite* AnimatedSprite::getInstance(int x, int y, int w, int h, std::string& imagePath) {
		return new AnimatedSprite(x, y, w, h, imagePath);
	}

	AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, std::string& imagePath) :Sprite(x, y, w, h)
	{
	}

	AnimatedSprite::~AnimatedSprite()
	{
	}
	void AnimatedSprite::draw() const
	{
	}
}
