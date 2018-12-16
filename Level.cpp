#include "Level.h"

namespace planeGameEngine {

	Level* Level::getInstance(std::string & name, std::vector<Sprite*> sprites) { return new Level(name, sprites); }
	Level* Level::getInstance(std::vector<Sprite*> sprites) { return new Level(sprites); }
	Level* Level::getInstance(std::string & name) { return new Level(name); }
	Level* Level::getInstance() { return new Level(); }

	Level::Level(std::string& name, std::vector<Sprite*> sprites) :levelName(name), levelSprites(sprites) {}
	Level::Level(std::vector<Sprite*> sprites) : levelSprites(sprites)
	{
		defaultLevelCounter++;
		this->levelName = "Level " + defaultLevelCounter;
	}

	Level::Level(std::string & name) : levelName(name)
	{ }
	Level::Level() {
		defaultLevelCounter++;
		this->levelName = "Level " + defaultLevelCounter;
	}

	Sprite* Level::addSprite(Sprite* sprite)
	{
		levelSprites.push_back(sprite);
		return sprite;
	}

	std::vector<Sprite*> Level::getLevelSprites()
	{
		return levelSprites;
	}

	Level::~Level()
	{
		for (Sprite* s : levelSprites) {
			delete s;
		}
	}
	int Level::defaultLevelCounter = 0;

}
