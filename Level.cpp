#include "Level.h"

namespace planeGameEngine {

	Level* Level::getInstance(std::string & name, std::vector<Sprite*> sprites) { return new Level(name, sprites); }
	Level* Level::getInstance(std::vector<Sprite*> sprites) { return new Level(sprites); }
	Level* Level::getInstance(std::string & name) { return new Level(name); }
	Level* Level::getInstance(int killCount) { return new Level(killCount); }

	Level::Level(std::string& name, std::vector<Sprite*> sprites) :levelName(name), levelSprites(sprites) {}
	Level::Level(std::vector<Sprite*> sprites) : levelSprites(sprites)
	{
		defaultLevelCounter++;
		this->levelName = "Level " + defaultLevelCounter;
	}

	Level::Level(std::string & name) : levelName(name)
	{ }
	Level::Level(int killCount): requiredKillCount(killCount) {
		defaultLevelCounter++;
		this->levelName = "Level " + defaultLevelCounter;
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
		for (Sprite* s : levelSprites) {
			delete s;
		}
	}
	int Level::defaultLevelCounter = 0;

}
