#ifndef CONTROLLABLESPRITE_H
#define CONTROLLABLESPRITE_H
#include "MovingSprite.h"

namespace planeGameEngine {

	class ControllableSprite: virtual public MovingSprite
	{
	public:
		static ControllableSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight, int hp);
		static ControllableSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp);
		void tick(const int iteractionCount);
		
		virtual void mouseDown(const SDL_Event& event);
		virtual void mouseUp(const SDL_Event& event);
		virtual void keyDown(const SDL_Event& event);
		virtual void keyUp(const SDL_Event& event);
		void setMoveDown(bool down) { moveDown = down; }
		void setMoveUp(bool up) { moveUp = up; }
		void setMoveLeft(bool left) { moveLeft = left; }
		void setMoveRight(bool right) { moveRight = right; }

		~ControllableSprite();
	protected:
		ControllableSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp);
		ControllableSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp);
		void determineMoveDirection();
	
	private:
		bool moveUp, moveDown, moveLeft, moveRight;
	};
}
#endif 

