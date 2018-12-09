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
		void run();
		
		~GameEngine();

	private:
		std::vector<Sprite*> sprites;
	};

}
#endif