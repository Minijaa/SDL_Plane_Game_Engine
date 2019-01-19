#include "GameEngine.h"
#include "System.h"
#include "MovingSprite.h"
#include <iostream>
#include "FuncShortCommand.h"

using namespace std;

namespace planeGameEngine {

	GameEngine::GameEngine() :activeLevelNumber(0), FRAMERATE(60) {}
	GameEngine::GameEngine(int fps) : activeLevelNumber(0), FRAMERATE(fps) {}
	void GameEngine::addMemFuncShortCommand(ShortCommand* mfunc) { shortCommands.push_back(mfunc); }
	void GameEngine::addSprite(Sprite* sprite) { spritesToAdd.push_back(sprite); }
	void GameEngine::removeSprite(Sprite* sprite) { spritesToRemove.push_back(sprite); }
	void GameEngine::addFuncShortCommand(char keyDown, void(*f)()) {
		shortCommands.push_back(FuncShortCommand::getInstance(keyDown, f));
	}

	void GameEngine::run() {
		sprites = levels[activeLevelNumber]->getLevelSprites();
		for (Sprite* s : sprites) {
			s->incrementRefCount();
		}
		activeLevel = levels[activeLevelNumber];
		activeLevel->setActiveLevel(true);
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

			checkForCollisions();

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

	//Checks for collisions between sprites and initiates action functions.
	void GameEngine::checkForCollisions()
	{
		for (Sprite* s : sprites) {
			if (s->isInteractable() && !s->isCollisionHandeled()) {
				for (Sprite* other : sprites) {
					if (other->isInteractable() && s != other && !other->isCollisionHandeled()) {
						if (s->collisionDetected(other)) {
							s->collisionAction(other, s->getCollisionWeight() < other->getCollisionWeight());
							s->setCollisionHandeled(true);
							other->collisionAction(s, other->getCollisionWeight() < s->getCollisionWeight());
							other->setCollisionHandeled(true);
							if (s->bounceIsActivated()) {
								s->bounce(other);
							}
							if (other->bounceIsActivated()) {
								other->bounce(s);
							}
						}
					}
				}
			}
			if (!paused) {
				s->tick();
			}
		}
	}

	Level* GameEngine::addLevel() {
		Level* level = Level::getInstance();
		levels.push_back(level);
		return level;
	}

	GameEngine::~GameEngine() {
		for (Level* l : levels) {
			delete l;
		}

		for (ShortCommand* sc : shortCommands) {
			delete sc;
		}
		for (Sprite* s : sprites) {
			if (s != nullptr) {
				s->decrementRefCount();
				if (s->getRefCount() == 0) {
					delete s;
				}
			}
		}
	}
	void GameEngine::RenderSprites(int nextTick)
	{
		//Render sprites for the current frame
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

	void GameEngine::changeLevel(bool nextLevel)
	{
		if (nextLevel) {
			if (levelToChangeToNr == -1 && (activeLevelNumber + 1) < levels.size()) {
				activeLevelNumber++;
			}
			else {
				activeLevelNumber = levelToChangeToNr;
			}
			SDL_RenderClear(sys.getRenderer());
			activeLevel->setActiveLevel(false);

			//Remove current game Sprites if they aren't stored elsewhere
			for (Sprite* s : sprites) {
				if (s != nullptr) {
					s->decrementRefCount();
					if (s->getRefCount() == 0) {
						delete s;
					}
					else {
						s->resetSpriteInstance();
					}
				}
			}
			//Load in sprites from new level
			sprites.clear();
			sprites = levels[activeLevelNumber]->getLevelSprites();
			for (Sprite* s : sprites) {
				s->incrementRefCount();
			}
			levelChange = false;
			activeLevel = levels[activeLevelNumber];
			activeLevel->setActiveLevel(true);
		}
	}
}
