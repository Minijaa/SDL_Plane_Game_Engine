#include "ControllableSprite.h"

namespace planeGameEngine {
	ControllableSprite::ControllableSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp) : Sprite(x, y, w, h, true), MovingSprite(x, y, w, h, moveDirection, speed, collissionWeight, hp) {}
	void ControllableSprite::determineMoveDirection() {
		if (alive) {
			if (moveUp && moveRight && getRect().y > 0 && getRect().x < (sys.getXResolution() - getRect().w)) {
				setDirection(MovingSprite::MOVEUPRIGHT);
			}
			else if (moveUp && moveLeft && getRect().y > 0 && getRect().x > 0) {
				setDirection(MovingSprite::MOVEUPLEFT);
			}
			else if (moveDown && moveRight && getRect().y < (sys.getYResolution() - getRect().h) && getRect().x < (sys.getXResolution() - getRect().w)) {
				setDirection(MovingSprite::MOVEDOWNRIGHT);
			}
			else if (moveDown && moveLeft && getRect().y < (sys.getYResolution() - getRect().h) && getRect().x > 0) {
				setDirection(MovingSprite::MOVEDOWNLEFT);
			}
			else if (moveDown && !moveUp && getRect().y < (sys.getYResolution() - getRect().h)) {
				setDirection(MovingSprite::MOVEDOWN);
			}
			else if (moveUp && !moveDown && getRect().y > 0) {
				setDirection(MovingSprite::MOVEUP);
			}
			else if (moveLeft && !moveRight && getRect().x > 0) {
				setDirection(MovingSprite::MOVELEFT);
			}
			else if (moveRight && !moveLeft && getRect().x < (sys.getXResolution() - getRect().w)) {
				setDirection(MovingSprite::MOVERIGHT);
			}
			else {
				setDirection(MovingSprite::MOVESTOP);
			}
		}
	}
	ControllableSprite * ControllableSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp) {
		return new ControllableSprite(x, y, w, h, moveDirection, speed, colissionWeight, hp);
	}
	void ControllableSprite::tick() {
		determineMoveDirection();
		MovingSprite::tick();
	}
	void ControllableSprite::implementBasicMovement(const SDL_Event& event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				moveUp = getRect().y > 0;
				break;
			case SDLK_DOWN:
				moveDown = getRect().y < (sys.getYResolution() - getRect().h);
				break;
			case SDLK_LEFT:
				moveLeft = getRect().x > 0;
				break;
			case SDLK_RIGHT:
				moveRight = getRect().x < (sys.getXResolution() - getRect().w);
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				moveUp = false;
				break;
			case SDLK_DOWN:
				moveDown = false;
				break;
			case SDLK_LEFT:
				moveLeft = false;
				break;
			case SDLK_RIGHT:
				moveRight = false;
				break;
			}
		}
	}
}