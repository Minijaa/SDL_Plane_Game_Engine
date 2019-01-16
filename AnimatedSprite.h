#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "Sprite.h"
#include <string>
#include "MovingSprite.h"
#include <unordered_map>
#include <vector>
#include <iostream>
namespace planeGameEngine {
	class AnimatedSprite : virtual public Sprite
	{
	public:
		static AnimatedSprite* getInstance(int x, int y, int w, int h, std::string& defaultImage);
		~AnimatedSprite();
		void draw() const;
		void tick();
		void setActiveEvent(std::string nameOfEvent);
		void addAnimation(std::string eventName, std::vector<std::string> paths);

	protected:
		AnimatedSprite(int x, int y, int w, int h, std::string& defaultImage);
	private:
		unsigned intervalCounter;
		int eventCounter;
		bool eventAnimationActive = false;
		void idleAnimation(int intervalCounter);
		void eventAnimation(int intervalCounter);
		std::unordered_map<std::string, std::vector<SDL_Texture*>> animationSpriteTextures;
		std::string activeEvent;
		SDL_Texture* activeSpriteTexture;
		SDL_Texture* defaultSpriteTexture;
		SDL_Texture* lastAnimationTexture;
		void makeTextures(std::string& defaultSprite);
	};
}
#endif