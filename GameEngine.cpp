#include "GameEngine.h"
#include "System.h"

namespace planeGameEngine {

	GameEngine::GameEngine()
	{
	}

	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
	}
	void GameEngine::remove(Sprite* sprite) {
		//Spara grejjer som ska tas bort i ta bort-vector
	}
	void GameEngine::run() {
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

			//Render stuff for the current frame
			SDL_RenderClear(sys.getRenderer());
			//Discover collisions
			for (Sprite* s : sprites) {
				if (s->isInteractable()) {
					for (Sprite* otherSprite : sprites) {
						if (otherSprite->isInteractable()) {
							if (SDL_HasIntersection(&s->getRect(), &otherSprite->getRect())) {
								s->collisionAction(otherSprite, s->getCollisionWeight() < otherSprite->getCollisionWeight());
							}
						}
					}
				}
				s->draw();
				s->tick(iterationCount);
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

		} //Outer while loop
	}

	int GameEngine::getIterationCount()
	{
		return iterationCount;
	}

	GameEngine::~GameEngine()
	{
	}

}
