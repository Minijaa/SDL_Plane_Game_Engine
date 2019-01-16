#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Sprite.h"
#include "Level.h"
#include "ShortCommand.h"
#include "MemFuncShortCommand.h"
#include "FuncShortCommand.h"

namespace planeGameEngine {

	class GameEngine
	{

	public:
		//struct ShortCommand;
		GameEngine();
		GameEngine(int fps);
		void addSprite(Sprite*);
		void removeSprite(Sprite*);
		Level* getActiveLevel() const { return activeLevel; }
		void addFuncShortCommand(char keyDown, void(*f)());
		void addMemFuncShortCommand(ShortCommand* mfunc);
		void run();

		int getIterationCount() const;
		void setLevelChange(bool value, int levelNr) { levelChange = value; levelToChangeToNr = levelNr; }
		void setPause(bool pause) { paused = pause; }
		bool isPaused() const { return paused; }
		//void setResetGame(bool value) { resetGame = value; }
		//void resetTheGame(bool value);
		Level* addLevel() {
			Level* level = Level::getInstance();
			levels.push_back(level);
			return level;
		}
		GameEngine* getEngine() {
			return this;
		}
		~GameEngine();

	private:
		bool paused = false;
		const int FRAMERATE;
		const int TICKINTERVAL = 1000 / FRAMERATE;
		std::vector<Sprite*> sprites, spritesToAdd, spritesToRemove;
		std::vector<Level*> levels;
		std::vector<ShortCommand*> shortCommands;
		int iterationCount, levelToChangeToNr;
		int activeLevelNumber = 0;
		Level* activeLevel;
		bool levelChange = false;
		void RenderSprites(int nextTick);
		void changeLevel(bool nextLevel);
	};
}
#endif