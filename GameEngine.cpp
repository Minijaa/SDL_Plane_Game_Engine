#include "GameEngine.h"
#include "System.h"
#include "MovingSprite.h"
#include <iostream>
using namespace std;

namespace planeGameEngine {

	struct GameEngine::ShortCommand {
		ShortCommand(char k, void(*f)()) :key(k), func(f) {}

		void action(SDL_Event event) {
			if (event.key.keysym.sym == key) {
				func();
			}
		}
	private:
		char key;
		void(*func)();
	};

	GameEngine::GameEngine() :activeLevelNumber(0), FRAMERATE(60)
	{
	}

	GameEngine::GameEngine(int fps) : activeLevelNumber(0), FRAMERATE(fps)
	{
	}

	void GameEngine::addShortCommand(char keyDown, void(*f)()) {
		shortCommands.push_back(new ShortCommand(keyDown, f));
	}

	void GameEngine::addSprite(Sprite* sprite) {
		spritesToAdd.push_back(sprite);
	}

	void GameEngine::removeSprite(Sprite* sprite) {
		spritesToRemove.push_back(sprite);
	}
	void GameEngine::run() {
		sprites = levels[activeLevelNumber]->getLevelSprites();
		bool running = true;
		while (running) {
			Uint32 nextTick = SDL_GetTicks() + TICKINTERVAL;
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					for (ShortCommand* sc : shortCommands) {
						sc->action(event);
					}
					for (Sprite* s : sprites) {
						s->keyDown(event);
					}break;
				case SDL_KEYUP:
					for (Sprite* s : sprites) {
						s->keyUp(event);
					}break;
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite* s : sprites) {
						s->mouseDown(event);
					}break;
				case SDL_MOUSEBUTTONUP:
					for (Sprite* s : sprites) {
						s->mouseUp(event);
					}break;
				case SDL_TEXTINPUT:
					for (Sprite* s : sprites) {
						s->input(event);
					}break;
				} //Switch
			} //Inner while loop

			//Discover collisions
			for (Sprite* s : sprites) {
				if (s->isInteractable() && !s->isCollisionHandeled()) {
					for (Sprite* other : sprites) {
						if (other->isInteractable() && s != other && !other->isCollisionHandeled()) {
							if (SDL_HasIntersection(&s->getRect(), &other->getRect())) {
								s->collisionAction(other, s->getCollisionWeight() < other->getCollisionWeight());
								s->setCollisionHandeled(true);
								other->collisionAction(s, other->getCollisionWeight() < s->getCollisionWeight());
								other->setCollisionHandeled(true);
							}
						}
					}
				}
				s->tick();
			}

			//Add added Sprites to main Sprite-vector
			for (Sprite* s : spritesToAdd) {
				sprites.push_back(s);
			}
			spritesToAdd.clear();

			//Remove flagged Sprites from main Sprite-vector
			for (Sprite* s : spritesToRemove) {
				for (vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end();) {
					if (*i == s) {
						i = sprites.erase(i);
						delete s;
					}
					else {
						i++;
					}
				}
			}
			spritesToRemove.clear();
			RenderSprites(nextTick);
			changeLevel(levelChange);


		} //Outer while loop
	}

	int GameEngine::getIterationCount()
	{
		return iterationCount;
	}

	GameEngine::~GameEngine()
	{
		for (Sprite* s : sprites) {
			delete s;
		}

	}
	void GameEngine::RenderSprites(int nextTick)
	{
		//Render stuff for the current frame
		SDL_RenderClear(sys.getRenderer());
		for (Sprite*s : sprites) {
			s->setCollisionHandeled(false);
			s->draw();
		}
		SDL_RenderPresent(sys.getRenderer());
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0) {
			SDL_Delay(delay);
		}
		if (iterationCount < INT32_MAX) {
			iterationCount++;
		}
		else {
			iterationCount = 0;
		}
	}
	void GameEngine::removeCurrentLevelSprites() {
		//Remove current game Sprites
		for (Sprite* s : sprites) {
			if (!s->surviveLevelChange()) {
				removeSprite(s);
			}
		}
	}
	void GameEngine::changeLevel(bool nextLevel)
	{
		if (nextLevel) {
			if (levelToChangeToNr == -1 && (activeLevelNumber + 1) < levels.size()) {
				removeCurrentLevelSprites();
				activeLevelNumber++;
				//Load in sprites from new level
				sprites = levels[activeLevelNumber]->getLevelSprites();
				levelChange = false;
			}
		}
	}
}
