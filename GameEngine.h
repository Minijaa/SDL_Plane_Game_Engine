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
		GameEngine(int fps);
		void addSprite(Sprite*);
		void removeSprite(Sprite*);
		void addShortCommand(char keyDown, void(*f)());
		void run();
		int getIterationCount();
		void setLevelChange(bool value, int levelNr) { levelChange = value; levelToChangeToNr = levelNr; }

		//void setResetGame(bool value) { resetGame = value; }
		//void resetTheGame(bool value);
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
		const int FRAMERATE;
		const int TICKINTERVAL = 1000 / FRAMERATE;
		std::vector<Sprite*> sprites, spritesToAdd, spritesToRemove;
		std::vector<Level*> levels;
		std::vector<ShortCommand*> shortCommands;
		int iterationCount, levelToChangeToNr;
		int activeLevelNumber = 0;
		Level* activeLevel;
		bool levelChange = false;
		//bool resetGame = false;
		void RenderSprites(int nextTick);
		void changeLevel(bool nextLevel);
		//void removeCurrentLevelSprites();
	};
}
#endif