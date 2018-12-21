#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Sprite.h"
#include "Level.h"

namespace planeGameEngine {

	class GameEngine
	{

	public:
		struct ShortCommand;
		GameEngine();
		void addSprite(Sprite*);
		void removeSprite(Sprite*);
		void addShortCommand(char keyDown, void(*f)());
		void run();
		int getIterationCount();
		void setIncomingLevelChange(bool value) { incomingLevelChange = value; }
		Level* addLevel(int killCount) {
			Level* level = Level::getInstance(killCount);
			levels.push_back(level);
			return level;
		}
		GameEngine* getEngine() {
			return this;
		}
		~GameEngine();

	private:
		const int FRAMERATE = 60;
		const int TICKINTERVAL = 1000 / FRAMERATE;
		std::vector<Sprite*> sprites, spritesToAdd, spritesToRemove;
		std::vector<Level*> levels;
		std::vector<ShortCommand*> shortCommands;
		Level* activeLevel;
		int iterationCount;
		int activeLevelNumber;
		bool incomingLevelChange;
	};

}
#endif