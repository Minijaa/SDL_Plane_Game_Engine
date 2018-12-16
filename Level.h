#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "Sprite.h"

namespace planeGameEngine {

	class Level
	{
	public:
		static Level* getInstance(std::string& name, std::vector<Sprite*> sprites);
		static Level* getInstance(std::vector<Sprite*> sprites);
		static Level* getInstance(std::string& name);
		static Level* getInstance(int killCount);

		std::string getLevelName() const { return levelName; }
		int getKillCount() const { return killCounter; }
		int getRequiredKillCount() const { return requiredKillCount; }
		int getDefaultLevelCounter() const { return defaultLevelCounter; }
		void incrementKillCounter() { killCounter++; }
		Sprite* addSprite(Sprite* sprite);
		void addSprite(std::vector<Sprite*> sprites);
		std::vector<Sprite*> getLevelSprites();
		~Level();
	protected:
		Level(std::string& name, std::vector<Sprite*> sprites);
		Level(std::vector<Sprite*> sprites);
		Level(std::string& name);
		Level(int killCount);

	private:
		std::string levelName;
		std::vector<Sprite*> levelSprites;
		int killCounter = 0; //Can be used for instance if level should be switched when the player has reached a chosen kill count
		int requiredKillCount;
		static int defaultLevelCounter; // Use to generate levelnumber if implementer don't want to implement "real levels".
	};

}
#endif // !LEVEL_H
