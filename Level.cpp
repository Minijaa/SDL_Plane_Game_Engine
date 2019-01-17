#include "Level.h"
namespace planeGameEngine {

	Level* Level::getInstance() { return new Level(); }

	Level::Level() {
		defaultLevelCounter++;
		levelName = "Level " + defaultLevelCounter;
	}
	Sprite* Level::addSprite(Sprite* sprite)
	{
		sprite->incrementRefCount();
		levelSprites.push_back(sprite);
		return sprite;
	}

	void Level::addSprite(std::vector<Sprite*> sprites)
	{
		for (Sprite* s : sprites) {
			s->incrementRefCount();
			levelSprites.push_back(s);
		}
	}

	std::vector<Sprite*> Level::getLevelSprites()
	{
		return levelSprites;
	}

	Level::~Level()
	{
		for (Sprite* s : levelSprites) {
			if (s != nullptr) {
				s->decrementRefCount();
				if (s->getRefCount() == 0) {
					delete s;
				}
			}
		}
	}
	int Level::defaultLevelCounter = 0;

}
