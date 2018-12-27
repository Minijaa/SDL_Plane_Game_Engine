#include "MovingSprite.h"


namespace planeGameEngine {

	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp)
	{
		makeTexture(imagePath);
	}

	MovingSprite::MovingSprite(int x, int y, int w, int h, moveDirections moveDirection, int speed, int collissionWeight, int hp) : Sprite(x, y, w, h, true), moveDir(moveDirection), moveSpeed(speed), weight(collissionWeight), healthPoints(hp)
	{
	}
	MovingSprite* MovingSprite::makeTexture(std::string& imagePath)
	{
		spriteTexture = IMG_LoadTexture(sys.getRenderer(), imagePath.c_str());
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
		return nullptr;
	}

	void MovingSprite::move()
	{
		//Use for UFO later.
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
		case MOVEUPLEFT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x - moveSpeed, getRect().y - moveSpeed);
			}
			break;
		case MOVEUPRIGHT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x + moveSpeed, getRect().y - moveSpeed);
			}
			break;
		case MOVEDOWNLEFT:
			if (getRect().x < 0 - getRect().w) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x - moveSpeed, getRect().y + moveSpeed);
			}
			break;
		case MOVEDOWNRIGHT:
			if (getRect().y > sys.getYResolution()) {
				outOfBoundsAction(&getRect(), MOVELEFT);
			}
			else {
				setXY(getRect().x + moveSpeed, getRect().y + moveSpeed);
			}
			break;
		case MOVESTOP:
			setXY(getRect().x, getRect().y);
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
	void MovingSprite::draw() const {
		SDL_RenderCopy(sys.getRenderer(), spriteTexture, NULL, &getRect());
	}
	MovingSprite::~MovingSprite()
	{
		SDL_DestroyTexture(spriteTexture);
	}
}
