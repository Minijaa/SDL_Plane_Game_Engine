#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "Sprite.h"
#include <string>
#include "MovingSprite.h"
#include <unordered_map>
#include <vector>

namespace planeGameEngine {

	class AnimatedSprite : virtual public Sprite
	{
	public:
		static AnimatedSprite* getInstance(int x, int y, int w, int h, std::unordered_map<std::string, std::string>, std::string& defaultImage);
		//, std::string& imagePath
		~AnimatedSprite();
		void draw() const;
		void tick(const int intervalCounter);
		void setActiveEvent(std::string& nameOfEvent);
	protected:
		AnimatedSprite(int x, int y, int w, int h, std::unordered_map<std::string, std::string> animationSpriteSheets, std::string& defaultImage);
		AnimatedSprite(int x, int y, int w, int h, std::unordered_map<std::string, std::vector<std::string>> animationSprites, std::string& defaultImage);
	private:
		bool eventAnimationActive = false;
		void idleAnimation(int intervalCounter);
		void eventAnimation(int intervalCounter, std::string& animationName);
		std::unordered_map<std::string, std::vector<std::string>> animationSprites;
		std::unordered_map<std::string, std::string> animationSpriteSheets;

		std::unordered_map<std::string, std::vector<SDL_Texture*>> animationSpriteTextures;
		std::string activeEvent;
		SDL_Texture* activeSpriteTexture;
		SDL_Texture* defaultSpriteTexture;
		void makeTextures(std::string& defaultSprite);
	};

}
#endif