#include "MovingSprite.h"


namespace planeGameEngine {
	//MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed) :Sprite(x, y, w, h), moveDir(moveDirection), moveSpeed(speed)
	//{
	//}
	//MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath) :Sprite(x, y, w, h), moveDir(moveDirection), moveSpeed(speed)
	//{
	//	makeTexture(imagePath);
	//}
	//MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight)
	//{
	//	makeTexture(imagePath);
	//}
	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp)
	{
		makeTexture(imagePath);
	}

	void MovingSprite::makeTexture(std::string& imagePath)
	{
		spriteTexture = IMG_LoadTexture(sys.getRenderer(), imagePath.c_str());
		if (spriteTexture == nullptr) {
			throw std::runtime_error("Sprite image not found");
		}
		/*if (SDL_QueryTexture(spriteTexture, NULL, NULL, &width, &height) == 0) {
			setWH(width, height);
		}*/
		/*else {
			throw std::runtime_error(SDL_GetError());
		}*/
	}

	/*MovingSprite* MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath)
	{
		return new MovingSprite(x, y, w, h, moveDirection, speed, imagePath);
	}

	MovingSprite* MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight)
	{
		return nullptr;
	}*/
	MovingSprite * MovingSprite::getInstance(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int colissionWeight, int hp)
	{
		return new MovingSprite(x, y, w, h, moveDirection, speed, imagePath, colissionWeight, hp);
	}

	void MovingSprite::move()
	{
		switch (moveDir) {
		case MOVELEFT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x - moveSpeed, getRect().y);
			}
			break;
		case MOVERIGHT:
			if (getRect().x > sys.getXResolution()) {
				outOfBoundsAction(&getRect(), MOVERIGHT);

			}
			else {
				setXY(getRect().x + moveSpeed, getRect().y);
			}
			break;
		case MOVEUP:
			if (getRect().y < 0 - getRect().h) {
				outOfBoundsAction(&getRect(), MOVEUP);

			}
			else {
				setXY(getRect().x, getRect().y - moveSpeed);
			}
			break;
		case MOVEDOWN:
			if (getRect().y > sys.getYResolution()) {
				outOfBoundsAction(&getRect(), MOVEDOWN);
			}
			else {
				setXY(getRect().x, getRect().y + moveSpeed);
			}
			break;
		case MOVESTOP:
			break;
		}
	}

	/*void MovingSprite::collisionCheck()
	{
		
	}*/

	void MovingSprite::setDirection(moveDirections moveDirection)
	{
	}

	void MovingSprite::tick()
	{
		move();
		//if (isInteractable) {
		//	//collisionCheck();
		//}
	}
	void MovingSprite::draw() const {
		SDL_RenderCopy(sys.getRenderer(), spriteTexture, NULL, &getRect());
	}
	MovingSprite::~MovingSprite()
	{
		SDL_DestroyTexture(spriteTexture);
	}
}
