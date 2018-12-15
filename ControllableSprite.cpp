#include "ControllableSprite.h"

namespace planeGameEngine {
	ControllableSprite::~ControllableSprite()
	{
	}
	ControllableSprite::ControllableSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string & imagePath, int collissionWeight, int hp) :Sprite(x, y, w, h, true), MovingSprite(x, y, w, h, moveDirection, speed, imagePath, collissionWeight, hp)
	{
	}
	ControllableSprite::ControllableSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp) : Sprite(x, y, w, h, true), MovingSprite(x, y, w, h, moveDirection, speed, collissionWeight, hp)
	{
	}
	void ControllableSprite::determineMoveDirection()
	{
		if (moveUp && moveRight) {
			setDirection(MovingSprite::MOVEUPRIGHT);
		}
		else if (moveUp && moveLeft) {
			setDirection(MovingSprite::MOVEUPLEFT);
		}
		else if (moveDown && moveRight) {
			setDirection(MovingSprite::MOVEDOWNRIGHT);
		}
		else if (moveDown && moveLeft) {
			setDirection(MovingSprite::MOVEDOWNLEFT);
		}
		else if (moveDown && !moveUp) {
			setDirection(MovingSprite::MOVEDOWN);
		}
		else if (moveUp && !moveDown) {
			setDirection(MovingSprite::MOVEUP);
		}
		else if (moveLeft && !moveRight) {
			setDirection(MovingSprite::MOVELEFT);
		}
		else if (moveRight && !moveLeft) {
			setDirection(MovingSprite::MOVERIGHT);
		}
		else {
			setDirection(MovingSprite::MOVESTOP);
		}
	}
	ControllableSprite * ControllableSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string & imagePath, int colissionWeight, int hp)
	{
		return nullptr;
	}
	ControllableSprite * ControllableSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp)
	{
		return nullptr;
	}
	void ControllableSprite::tick(const int iteractionCount)
	{
		determineMoveDirection();
		MovingSprite::tick(0);
	}
	void ControllableSprite::implementBasicMovement(const SDL_Event& event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				moveUp = true;
				break;
			case SDLK_DOWN:
				moveDown = true;
				break;
			case SDLK_LEFT:
				moveLeft = true;
				break;
			case SDLK_RIGHT:
				moveRight = true;
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
	void ControllableSprite::mouseDown(const SDL_Event & event)
	{
	}
	void ControllableSprite::mouseUp(const SDL_Event & event)
	{
	}
	void ControllableSprite::keyDown(const SDL_Event & event)
	{
	}
	void ControllableSprite::keyUp(const SDL_Event & event)
	{
	}
}
