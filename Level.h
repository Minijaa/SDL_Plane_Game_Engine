#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "Sprite.h"

namespace planeGameEngine {

	class Level
	{
	public:
		static Level* getInstance();
		std::string getLevelName() const { return levelName; }
		int getDefaultLevelCounter() const { return defaultLevelCounter; }
		Sprite* addSprite(Sprite* sprite);
		void addSprite(std::vector<Sprite*> sprites);
		std::vector<Sprite*> getLevelSprites();
		void setActiveLevel(bool active) { activeLevel = active; }
		bool getActiveLevel() { return activeLevel; }
		~Level();
	protected:
		Level();

	private:
		std::string levelName;
		std::vector<Sprite*> levelSprites;
		bool activeLevel;
		int requiredKillCount;
		static int defaultLevelCounter; // Use to generate levelnumber if implementer don't want to implement "real levels".
	};
}
#endif
