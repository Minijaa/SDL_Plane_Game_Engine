#include "GameEngine.h"
#include "System.h"
#include "MovingSprite.h"
#include <iostream>
using namespace std;

namespace planeGameEngine {

	GameEngine::GameEngine() :activeLevelNumber(0)
	{
	}

	void GameEngine::add(Sprite* sprite) {
		spritesToAdd.push_back(sprite);
	}
	void GameEngine::remove(Sprite* sprite) {
		spritesToRemove.push_back(sprite);
	}
	void GameEngine::run() {
		activeLevel = levels[0];
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
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite* s : sprites) {
						s->mouseDown(event);
					}break;
				case SDL_MOUSEBUTTONUP:
					for (Sprite* s : sprites) {
						s->mouseUp(event);
					}break;
				case SDL_KEYDOWN:
					for (Sprite* s : sprites) {
						s->keyDown(event);
					}break;
				case SDL_KEYUP:
					for (Sprite* s : sprites) {
						s->keyUp(event);
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
				s->tick(iterationCount);
			}

			for (Sprite* s : spritesToAdd) {
				sprites.push_back(s);
			}
			spritesToAdd.clear();

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
			if (activeLevel->getKillCount() > activeLevel->getRequiredKillCount()) { //Det här blir knäppt att bestämma här. Måste göras i main på något sätt.
				incomingLevelChange = true;
			}
			if (incomingLevelChange) {
				int counter = 0;
				//Rätt fult, känns som hur levelbytet ska se ut borde avgöras av implementeraren. Eventuell "fada" bort alla sprites.
				//Check that all non-player moving sprites are removed before switching level
				for (Sprite* s : sprites) {
					if (s->getRect().x > 1280) {
						remove(s);
					}
					else {
					s->setFlagForDeletion(true);
					}
					if (!s->isInteractable()) {
						if (MovingSprite* ms = dynamic_cast<MovingSprite*>(s)) {
							ms->setMoveSpeed(5);
						}
					}
					if (s->getCollisionWeight() > 0) {
						counter++;
					}
				}if (counter < 2) {
					std::cout << "HEJ";
					activeLevelNumber++;
					sprites = levels[activeLevelNumber]->getLevelSprites(); // OBS!!! objekten i gamla sprites måste deletas
					activeLevel = levels[activeLevelNumber];
					incomingLevelChange = false;
					
				}
				//iterationCount++;
			}
			
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
}
