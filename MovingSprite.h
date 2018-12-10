#ifndef MOVINGSPRITE_H
#define MOVINGSPRITE_H
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "ImagePaths.h"
#include <string>
#include "System.h"

namespace planeGameEngine {

	class MovingSprite :public Sprite
	{
	private:
		int moveSpeed, moveDir, width, height;
		bool isInteractable;
		SDL_Texture* spriteTexture;
		void move();
		void collisionCheck();
		void makeTexture(std::string& imagePath);

	public:
		enum moveDirections { MOVELEFT, MOVERIGHT, MOVEDOWN, MOVEUP, MOVESTOP };
		static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath);
		static MovingSprite* getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight);
		
		int getMoveSpeed() const { return moveSpeed; }
		void setMoveSpeed(int speed) { moveSpeed = speed; }
		void setDirection(moveDirections moveDirection);
		void tick();
		void draw() const;
		virtual void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {}
		virtual void hitBoundryAction(SDL_Rect* rect) {} //Endast aktuell för Player och Ufo
		~MovingSprite();

	protected:
		MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath);
		MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight);

	};
}
#endif
