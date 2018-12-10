#include "GameEngine.h"
#include "System.h"

namespace planeGameEngine {

	GameEngine::GameEngine()
	{
	}

	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
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
			for (Sprite* s : sprites) {
				s->draw();
				s->tick();

			}
			SDL_RenderPresent(sys.getRenderer());
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0) {
				SDL_Delay(delay);
			}
		} //Outer while loop
	}

	GameEngine::~GameEngine()
	{
	}

}
