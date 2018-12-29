#include "AnimatedSprite.h"

namespace planeGameEngine {

	AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, std::string & defaultImage) :Sprite(x, y, w, h)
	{
		makeTextures(defaultImage);
	}
	AnimatedSprite * AnimatedSprite::getInstance(int x, int y, int w, int h, std::string & defaultImage)
	{
		return new AnimatedSprite(x, y, w, h, defaultImage);
	}
	AnimatedSprite::~AnimatedSprite()
	{
		SDL_DestroyTexture(activeSpriteTexture);
		SDL_DestroyTexture(defaultSpriteTexture);
		SDL_DestroyTexture(lastAnimationTexture);

		if (!animationSpriteTextures.empty()) {
			for (auto iter = animationSpriteTextures.begin(); iter != animationSpriteTextures.end(); iter++) {
				for (SDL_Texture* tx : iter->second) {
					SDL_DestroyTexture(tx);
				}
			}
		}
	}
	void AnimatedSprite::draw() const
	{
		SDL_RenderCopy(sys.getRenderer(), activeSpriteTexture, NULL, &getRect());
	}
	void AnimatedSprite::tick()
	{
		intervalCounter++;
		if (!animationSpriteTextures.empty()) { //Måste fixas och kolla om "idle" inte pekar på nåt vettigt
			if (!eventAnimationActive) {
				idleAnimation(intervalCounter);
			}
			else {
				eventAnimation(intervalCounter);
			}
		}
	}

	void AnimatedSprite::setActiveEvent(std::string nameOfEvent)
	{
		eventAnimationActive = true;
		activeEvent = nameOfEvent;
	}

	void AnimatedSprite::addAnimation(std::string eventName, std::vector<std::string> paths)
	{
		//animationSprites[eventName] = paths;
		for (std::string s : paths) {
			SDL_Texture* tx = IMG_LoadTexture(sys.getRenderer(), s.c_str());
			animationSpriteTextures[eventName].push_back(tx);
		}
	}

	void AnimatedSprite::idleAnimation(int intervalCounter) {

		std::vector<SDL_Texture*> atx = animationSpriteTextures["idle"];
		if ((intervalCounter % 4) == 0) {
			intervalCounter = 0;
			for (unsigned i = 0; i < atx.size(); i++) {
				if (activeSpriteTexture == defaultSpriteTexture) {
					activeSpriteTexture = atx[0];
					break;
				}
				if (activeSpriteTexture == atx[atx.size() - 1]) {
					activeSpriteTexture = defaultSpriteTexture;
					lastAnimationTexture = nullptr;
					break;
				}
				if (activeSpriteTexture == atx[i]) {
					activeSpriteTexture = atx[i + 1];
					break;
				}
			}
		}
	}
	void AnimatedSprite::eventAnimation(int intervalCounter) {
		std::vector<SDL_Texture*> etx = animationSpriteTextures[activeEvent];
		if ((intervalCounter % 2) == 0) {
			intervalCounter = 0;
			for (unsigned i = 0; i < etx.size(); i++) {
				if (lastAnimationTexture == nullptr) {
					activeSpriteTexture = etx[0];
					lastAnimationTexture = activeSpriteTexture;
					break;
				}
				if (activeSpriteTexture == etx[etx.size() - 1]) {
					activeSpriteTexture = defaultSpriteTexture;
					eventAnimationActive = false;
					lastAnimationTexture = nullptr;
					break;
				}
				if (activeSpriteTexture == etx[i]) {
					activeSpriteTexture = etx[i + 1];
					break;
				}
			}
		}
	}
	void AnimatedSprite::makeTextures(std::string& defaultSprite)
	{
		//för individuella sprites (inte spritesheets)
		/*if (!animationSprites.empty()) {
			for (auto iter = animationSprites.begin(); iter != animationSprites.end(); iter++) {
				for (std::string s : iter->second) {
					SDL_Texture* tx = IMG_LoadTexture(sys.getRenderer(), s.c_str());
					animationSpriteTextures[iter->first].push_back(tx);
				}
			}
		}*/
		activeSpriteTexture = IMG_LoadTexture(sys.getRenderer(), defaultSprite.c_str());
		defaultSpriteTexture = activeSpriteTexture;
		if (activeSpriteTexture == nullptr) {
			throw std::runtime_error("Sprite image not found");
		}
	}
}