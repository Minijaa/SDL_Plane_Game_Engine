#include "Level.h"

namespace planeGameEngine {

	Level * Level::getInstance(std::string & name, std::vector<Sprite*> sprites) { return new Level(name, sprites); }

	Level * Level::getInstance(std::vector<Sprite*> sprites) { return new Level(sprites); }

	Level::Level(std::string& name, std::vector<Sprite*> sprites) :levelName(name), levelSprites(sprites) {}

	Level::Level(std::vector<Sprite*> sprites) : levelSprites(sprites)
	{
		defaultLevelCounter++;
		this->levelName = "Level " + defaultLevelCounter;
	}

	Level::~Level()
	{
		for (Sprite* s : levelSprites) {
			delete s;
		}
	}
	int Level::defaultLevelCounter = 0;
	
}
