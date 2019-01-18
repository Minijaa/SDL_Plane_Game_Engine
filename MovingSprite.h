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
		int moveDir, width, height, healthPoints, weight;
		double moveSpeedX, moveSpeedY, moveSpeed;
		bool hasImage;
		SDL_Texture* spriteTexture;

		//void collisionCheck();

	public:
		enum moveDirections { MOVELEFT, MOVEUPLEFT, MOVEDOWN, MOVEUP, MOVERIGHT, MOVEUPRIGHT, MOVEDOWNLEFT, MOVEDOWNRIGHT, MOVESTOP };
		MovingSprite* makeTexture(std::string& imagePath);
		static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight, int hp);
		static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp);
		double getMoveSpeed() const { return moveSpeed; }
		void setMoveSpeed(double speed) { moveSpeed = speed; }
		
		void setDirection(moveDirections moveDirection);
		void setHp(int hp) { healthPoints = hp; }
		void tick();
		void draw();
		void move();
		int getCollisionWeight() const {
			return weight;
		}
		int getHp() const { return healthPoints; }
		void decreaseHp(int decreaseValue = 1) {
			healthPoints -= decreaseValue;
		}
		virtual void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {};
		virtual void hitBoundryAction(SDL_Rect* rect, int moveDirection) {} //Endast aktuell för Player och Ufo
		virtual void collisionAction(Sprite* sprite_1, Sprite* sprite_2) {}
		~MovingSprite();
		void bounce(Sprite* other);

	protected:
		MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp);
		MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp);

	};
}
#endif
