#include "AnimatedSprite.h"

namespace planeGameEngine {

	AnimatedSprite* AnimatedSprite::getInstance(int x, int y, int w, int h, std::unordered_map<std::string, std::string> animations, std::string& defaultImage) {
		//return new AnimatedSprite(x, y, w, h, imagePath);
		return nullptr;
	}

	AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, std::unordered_map<std::string, std::string> animations, std::string& defaultImage) :Sprite(x, y, w, h)
	{
		animationSpriteSheets.insert(animations.begin(), animations.end());
		makeTextures(defaultImage);
		//animationSpriteSheets["shooting"] = imagePath;
	}
	AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, std::unordered_map<std::string, std::vector<std::string>> animations, std::string& defaultImage) :Sprite(x, y, w, h) {
		animationSprites.insert(animations.begin(), animations.end());
		makeTextures(defaultImage);
	}
	AnimatedSprite::~AnimatedSprite()
	{
		
	}
	void AnimatedSprite::draw() const
	{
		SDL_RenderCopy(sys.getRenderer(), activeSpriteTexture, NULL, &getRect());

	}
	void AnimatedSprite::tick(const int intervalCounter)
	{
		if (!animationSprites.empty()) { //Måste fixas och kolla om "idle" inte pekar på nåt vettigt

			if (!eventAnimationActive) {
				idleAnimation(intervalCounter);
			}
			else {
				//eventAnimation(intervalCounter);
			}
		}
	}

	void AnimatedSprite::setActiveEvent(std::string & nameOfEvent)
	{
		activeEvent = nameOfEvent;
	}

	void AnimatedSprite::idleAnimation(int intervalCounter) {

		std::vector<SDL_Texture*> atx = animationSpriteTextures["idle"];
		if ((intervalCounter % 4) == 0) {
			for (unsigned i = 0; i < atx.size(); i++) {
				if (activeSpriteTexture == defaultSpriteTexture) {
					activeSpriteTexture = atx[0];
					break;
				}
				if (activeSpriteTexture == atx[atx.size() - 1]) {
					activeSpriteTexture = defaultSpriteTexture;
					break;
				}
				if (activeSpriteTexture == atx[i]) {
					activeSpriteTexture = atx[i + 1];
					break;
				}
			}
		}

	}
	void AnimatedSprite::eventAnimation(int intervalCounter, std::string& animationName) {
		SDL_Texture* lastAnimationTexture;
		if ((intervalCounter % 4) == 0) {
			for (SDL_Texture* tx : animationSpriteTextures[animationName]) {
				if (activeSpriteTexture == defaultSpriteTexture) {
					activeSpriteTexture = tx;
					lastAnimationTexture = tx;
					break;
				}
				if (activeSpriteTexture == tx) {

				}
			}
		}
	}
	void AnimatedSprite::makeTextures(std::string& defaultSprite)
	{
		//för individuella sprites (inte spritesheets)
		if (!animationSprites.empty()) {
			for (auto iter = animationSprites.begin(); iter != animationSprites.end(); iter++) {
				for (std::string s : iter->second) {
					SDL_Texture* tx = IMG_LoadTexture(sys.getRenderer(), s.c_str());
					animationSpriteTextures[iter->first].push_back(tx);
				}
			}
		}
		activeSpriteTexture = IMG_LoadTexture(sys.getRenderer(), defaultSprite.c_str());
		defaultSpriteTexture = activeSpriteTexture;
		if (activeSpriteTexture == nullptr) {
			throw std::runtime_error("Sprite image not found");
		}
	}
}