#include "Level.h"
namespace planeGameEngine {

	Level* Level::getInstance() { return new Level(); }

	Level::Level() {
		defaultLevelCounter++;
		levelName = "Level " + defaultLevelCounter;
	}
	Sprite* Level::addSprite(Sprite* sprite)
	{
		levelSprites.push_back(sprite);
		return sprite;
	}

	void Level::addSprite(std::vector<Sprite*> sprites)
	{
		for (Sprite* s : sprites) {
			levelSprites.push_back(s);
		}
	}

	std::vector<Sprite*> Level::getLevelSprites()
	{
		return levelSprites;
	}

	Level::~Level()
	{
		// Krashar vid extit!!
		/*for (Sprite* s : levelSprites) {
			if (!this->activeLevel) {
				delete s;
			}
		}*/
	}
	int Level::defaultLevelCounter = 0;

}
