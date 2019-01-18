#include "MovingSprite.h"
#include <iostream>

namespace planeGameEngine {
	
	void MovingSprite::bounce(Sprite* other)
	{
		moveSpeedX *= -1.0 *getElasticity();
		moveSpeedY *= -1.0 *getElasticity();
	}
	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp)
	{
		moveSpeedX = moveSpeed;
		moveSpeedY = moveSpeed;
		makeTexture(imagePath);
		hasImage = true;
	}

	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp)
	{
		moveSpeedX = moveSpeed;
		moveSpeedY = moveSpeed;
		hasImage = false;
	}
	MovingSprite* MovingSprite::makeTexture(std::string& imagePath)
	{
		SDL_Surface* surf = IMG_Load(imagePath.c_str());
		spriteTexture = SDL_CreateTextureFromSurface(sys.getRenderer(), surf);
		setSurf(surf);
		//if Texture size is undefined assign surf size to texture
		if (getRect().w == 0 || getRect().h == 0) {
			setWH(surf->w, surf->h);
		}
		if (spriteTexture == nullptr) {
			throw std::runtime_error("Sprite image not found");
		}
		return this;
	}

	MovingSprite* MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight, int hp)
	{
		return new MovingSprite(x, y, w, h, moveDirection, speed, imagePath, colissionWeight, hp);
	}

	MovingSprite* MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp)
	{
		return new MovingSprite(x, y, w, h, moveDirection, speed, colissionWeight, hp);
	}

	void MovingSprite::move()
	{
		double gravity;
		if (affectedByGravity()) {
			gravity = sys.getGravity();
		}
		else {
			gravity = 0.0;
		}
		//Check for collision with boundary
		if (getRect().x == 0 ||
			getRect().x == sys.getXResolution() - getRect().w ||
			getRect().y == 0 ||
			getRect().y == sys.getYResolution() - getRect().h) {
			hitBoundryAction(&getRect(), moveDir);
		}
		switch (moveDir) {
		case MOVELEFT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x - moveSpeed, getRect().y);
				
				//include gravity
				setXY(getRect().x, getRect().y + affectedByGravity()*(moveSpeed *gravity + moveSpeedY * gravity));
				moveSpeedY += gravity * 1.0;
			}
			break;
		case MOVERIGHT:
			if (getRect().x > sys.getXResolution()) {
				outOfBoundsAction(&getRect(), MOVERIGHT);
			}
			else {
				setXY(getRect().x + moveSpeedX, getRect().y );
				
				//include gravity
				setXY(getRect().x, getRect().y + affectedByGravity()*(moveSpeed + moveSpeedY * gravity));
				moveSpeedY += gravity * 1.0;
			}
			break;
		case MOVEUP:
			if (getRect().y < 0 - getRect().h) {
				outOfBoundsAction(&getRect(), MOVEUP);
			}
			else {
				setXY(getRect().x, getRect().y - moveSpeed);
				
				//include gravity
				setXY(getRect().x, getRect().y + moveSpeedY * gravity);
				moveSpeedY -= gravity * 1.0;
			}
			break;
		case MOVEDOWN:
			if (getRect().y > sys.getYResolution()) {
				outOfBoundsAction(&getRect(), MOVEDOWN);
			}
			else {
				setXY(getRect().x, getRect().y + moveSpeed);
				
				//include gravity
				setXY(getRect().x, getRect().y + moveSpeedY * gravity);
				moveSpeedY += gravity * 1.0;
			}
			break;
		case MOVEUPLEFT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);

			}
			else {
				setXY(getRect().x - moveSpeed, getRect().y - moveSpeedY);
				
				//include gravity
				setXY(getRect().x, getRect().y + moveSpeedY * gravity);
				moveSpeedY -= gravity * 1.0;
			}
			break;
		case MOVEUPRIGHT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x + moveSpeed, getRect().y - moveSpeed);
				
				//include gravity
				setXY(getRect().x, getRect().y + moveSpeedY * gravity);
				moveSpeedY -= gravity * 1.0;
			}
			break;
		case MOVEDOWNLEFT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x - moveSpeed, getRect().y + moveSpeed);
				
				//include gravity
				setXY(getRect().x, getRect().y + moveSpeedY * gravity);
				moveSpeedY += gravity * 1.0;
			}

			break;
		case MOVEDOWNRIGHT:
			if (getRect().y > sys.getYResolution()) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x + moveSpeed, getRect().y + moveSpeed);
				
				//include gravity
				setXY(getRect().x, getRect().y + moveSpeedY * gravity);
				moveSpeedY += gravity * 1.0;
			}
			break;
		case MOVESTOP:
			setXY(getRect().x, getRect().y);
			
			//include gravity
			setXY(getRect().x, getRect().y + moveSpeedY * gravity);
			moveSpeedY += gravity * 1.0;
			break;
		}	
	}


	void MovingSprite::setDirection(moveDirections moveDirection)
	{
		moveDir = moveDirection;
	}

	void MovingSprite::tick()
	{
		move();
	}
	void MovingSprite::draw() {
		SDL_RenderCopy(sys.getRenderer(), spriteTexture, NULL, &getRect());
	}
	MovingSprite::~MovingSprite()
	{
		//std::cout << "Moving Weight: " << weight << " RefCount: " << getRefCount() << std::endl;
		if (spriteTexture) {
			SDL_DestroyTexture(spriteTexture);
		}
		if (hasImage) {
			SDL_FreeSurface(getSurf());
		}

	}
}
