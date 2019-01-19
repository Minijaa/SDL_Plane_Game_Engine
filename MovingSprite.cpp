#include "MovingSprite.h"
#include <iostream>

namespace planeGameEngine {

	void MovingSprite::bounce(Sprite* other) {
		SDL_Rect rect = getRect();
		int centerX = rect.x + rect.w / 2;
		int centerY = rect.y + rect.h / 2;

		SDL_Rect oRect = other->getRect();
		int oCenterX = oRect.x + oRect.w / 2;
		int oCenterY = oRect.y + oRect.h / 2;

		//Determine which side of rectangle was hit, then change moveDirection to opposite direction.

		if ((oCenterX < centerX) && ((oCenterY < (centerY + rect.h / 2))
			&& (oCenterY > (centerY - rect.h / 2)))) {
			//Left side hit!
			moveDir = moveDirections::MOVERIGHT;
		}
		else if ((oCenterX > centerX) && ((oCenterY < (centerY + rect.h / 2))
			&& (oCenterY > (centerY - rect.h / 2)))) {
			//Right side hit!
			moveDir = moveDirections::MOVELEFT;
		}
		else if ((oCenterY < centerY) && ((oCenterX < (centerX + rect.w / 2))
			&& (oCenterX > (centerX - rect.w / 2)))) {
			//Top side hit!
			moveDir = moveDirections::MOVEDOWN;
		}
		else if ((oCenterY > centerY) && ((oCenterX < (centerX + rect.w / 2))
			&& (oCenterX > (centerX - rect.w / 2)))) {
			//Bottom side hit!
			moveDir = moveDirections::MOVEUP;
		}
		else if ((oCenterY < centerY) && (oCenterX > centerX)) {
			//Top right corner is hit!
			moveDir = moveDirections::MOVEDOWNLEFT;
		}
		else if ((oCenterY < centerY) && (oCenterX < centerX)) {
			//Top left corner is hit!
			moveDir = moveDirections::MOVEDOWNRIGHT;
		}
		else if ((oCenterY > centerY) && (oCenterX < centerX)) {
			//Bottom left corner is hit!
			moveDir = moveDirections::MOVEUPRIGHT;
		}
		else {
			//Bottom right corner is hit!
			moveDir = moveDirections::MOVEUPLEFT;
		}
		moveSpeed *= getElasticity();

	}
	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp) {
		makeTexture(imagePath);
		hasImage = true;
	}

	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp) {
		hasImage = false;
	}
	MovingSprite* MovingSprite::makeTexture(std::string& imagePath) {
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

	MovingSprite* MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight, int hp) {
		return new MovingSprite(x, y, w, h, moveDirection, speed, imagePath, colissionWeight, hp);
	}

	MovingSprite* MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, int colissionWeight, int hp) {
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
		//Check for out of bounds
		if (getRect().x > sys.getXResolution() ||
			getRect().x < 0 - getRect().w ||
			getRect().y < 0 - getRect().h ||
			getRect().y > sys.getYResolution()) {
			outOfBoundsAction(&getRect());
		}
		//Move according to move direction. If gravity is enabled gravity affects move direction
		switch (moveDir) {
		case MOVELEFT:
			setXY(getRect().x - moveSpeed, getRect().y + (gravityPullSpeed * gravity));
			break;
		case MOVERIGHT:
			setXY(getRect().x + moveSpeed, getRect().y + (gravityPullSpeed * gravity));
			break;
		case MOVEUP:
			setXY(getRect().x, getRect().y - moveSpeed + (gravityPullSpeed * gravity));
			break;
		case MOVEDOWN:
			setXY(getRect().x, getRect().y + moveSpeed + (gravityPullSpeed * gravity));
			break;
		case MOVEUPLEFT:
			setXY(getRect().x - moveSpeed, getRect().y - moveSpeed + (gravityPullSpeed * gravity));
			break;
		case MOVEUPRIGHT:
			setXY(getRect().x + moveSpeed, getRect().y - moveSpeed + (gravityPullSpeed * gravity));
			break;
		case MOVEDOWNLEFT:
			setXY(getRect().x - moveSpeed, getRect().y + moveSpeed + (gravityPullSpeed * gravity));
			break;
		case MOVEDOWNRIGHT:
			setXY(getRect().x + moveSpeed, getRect().y + moveSpeed + (gravityPullSpeed * gravity));
			break;
		case MOVESTOP:
			setXY(getRect().x, getRect().y + (gravityPullSpeed * gravity));
			break;
		}
		gravityPullSpeed += gravity * 1.0;
	}

	void MovingSprite::setDirection(moveDirections moveDirection) { moveDir = moveDirection; }
	void MovingSprite::tick() { move(); }
	void MovingSprite::draw() {
		SDL_RenderCopy(sys.getRenderer(), spriteTexture, NULL, &getRect());
	}
	MovingSprite::~MovingSprite() {
		if (spriteTexture) {
			SDL_DestroyTexture(spriteTexture);
		}
		if (hasImage) {
			SDL_FreeSurface(getSurf());
		}
	}
}
