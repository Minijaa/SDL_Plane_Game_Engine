#ifndef MOVINGSPRITE_H
#define MOVINGSPRITE_H
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "FilePaths.h"
#include <string>
#include "System.h"

namespace planeGameEngine {

	class MovingSprite : virtual public Sprite
	{
	private:
		int moveSpeed, moveDir, width, height, healthPoints, weight;
		SDL_Texture* spriteTexture;
		//void collisionCheck();
		void makeTexture(std::string& imagePath);

	public:
		enum moveDirections { MOVELEFT, MOVERIGHT, MOVEDOWN, MOVEUP, MOVEUPLEFT, MOVEUPRIGHT, MOVEDOWNLEFT, MOVEDOWNRIGHT, MOVESTOP };
		//static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath);
		//static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight);
		static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight, int hp);
		static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp);
		
		int getMoveSpeed() const { return moveSpeed; }
		void setMoveSpeed(int speed) { moveSpeed = speed; }

		void setDirection(moveDirections moveDirection);
		void setHp(int hp) { healthPoints = hp; }
		void tick(const int iteractionCount);
		void draw() const;
		void move();
		int getCollisionWeight() const {
			return weight;
		}
		int getHp() const { return healthPoints; }
		void decreaseHp(int decreaseValue = 1) {
			healthPoints -= decreaseValue;
		}
		virtual void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {};
		virtual void hitBoundryAction(SDL_Rect* rect) {} //Endast aktuell för Player och Ufo
		virtual void collisionAction(Sprite* sprite_1, Sprite* sprite_2) {}
		~MovingSprite();

	protected:
		//MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed);
		//MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath);
		//MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight);
		MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp);
		MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp);

	};
}
#endif
