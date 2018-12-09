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
		std::string getLevelName() const { return levelName; }
		int getKillCount() const { return killCounter; }
		int getDefaultLevelCounter() const { return defaultLevelCounter; }
		void incrementKillCounter() { killCounter++; }
		~Level();
	protected:
		Level(std::string& name, std::vector<Sprite*> sprites);
		Level(std::vector<Sprite*> sprites);

	private:
		std::string levelName;
		std::vector<Sprite*> levelSprites;
		int killCounter; //Can be used forinstance if level should be switched when the player has reached a chosen kill count
		static int defaultLevelCounter; // Use to generate levelnumber if implementer don't want to implement "real levels".
	};

#endif // !LEVEL_H
}
