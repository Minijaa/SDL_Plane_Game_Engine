#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Sprite.h"

namespace planeGameEngine {

	class GameEngine
	{
	public:
		GameEngine();
		void add(Sprite*);
		void remove(Sprite*);
		void run();
		int getIterationCount();
		GameEngine* getEngine() {
			return this;
		}
		~GameEngine();

	private:
		const int FRAMERATE = 60;
		const int TICKINTERVAL = 1000 / FRAMERATE;
		std::vector<Sprite*> sprites, spritesToAdd, spritesToRemove;
		int iterationCount;


	};

}
#endif