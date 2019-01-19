#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Sprite.h"
#include "Level.h"
#include "ShortCommand.h"
#include "MemFuncShortCommand.h"
#include "FuncShortCommand.h"

namespace planeGameEngine {

	class GameEngine {

	public:
		GameEngine();
		GameEngine(int fps);
		void addSprite(Sprite*);
		void removeSprite(Sprite*);
		Level* getActiveLevel() const { return activeLevel; }
		void addFuncShortCommand(char keyDown, void(*f)());
		void addMemFuncShortCommand(ShortCommand* mfunc);
		void run();
		void checkForCollisions();
		int getIterationCount() const { return iterationCount; }
		void setLevelChange(bool value, int levelNr) { levelChange = value; levelToChangeToNr = levelNr; }
		void setPause(bool pause) { paused = pause; }
		bool isPaused() const { return paused; }
		Level* addLevel(); 
		GameEngine* getEngine() { return this; }
		~GameEngine();

	private:
		const int FRAMERATE;
		const int TICKINTERVAL = 1000 / FRAMERATE;
		int iterationCount, levelToChangeToNr, activeLevelNumber;
		bool paused = false;
		bool levelChange = false;
		void RenderSprites(int nextTick);
		void changeLevel(bool nextLevel);
		Level* activeLevel;
		std::vector<Sprite*> sprites, spritesToAdd, spritesToRemove;
		std::vector<Level*> levels;
		std::vector<ShortCommand*> shortCommands;
	};
}
#endif