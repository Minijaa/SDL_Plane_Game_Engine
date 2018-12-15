#include <SDL.h>
#include "GameEngine.h"
#include "Background.h"
#include "ImagePaths.h"
#include "MovingSprite.h"
#include "AnimatedSprite.h"
#include "ControllableSprite.h"
#include <unordered_map>
#include <iostream>

using namespace planeGameEngine;
using namespace std;

const int minOutOfBoundsValue = 200;
const int maxOutOfBoundsValue = 600;
GameEngine game;
ImagePaths path;

//Implementation classes below
class Cloud : public MovingSprite {
public:
	Cloud(int x, int y, int w, int h, int speed, std::string& imagePath) : Sprite(x, y, w, h), MovingSprite(x, y, w, h, MovingSprite::MOVELEFT, speed, imagePath, NULL, NULL)
	{

	}
	void tick() {
		MovingSprite::tick(game.getIterationCount());
	}
	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), rect->y);
		int size = sys.generateRandomNumber(400, 256);
		setWH(size, size);
		setMoveSpeed(sys.generateRandomNumber(3, 1));
	}
};

class SpaceShip : public MovingSprite {
public:
	SpaceShip(int x, int y, int w, int h, MovingSprite::moveDirections moveDir, int speed, std::string& imagePath, int weight, int hp) : Sprite(x, y, w, h, true), MovingSprite(x, y, w, h, moveDir, speed, imagePath, weight, hp)
	{
		defaultHp = hp;
	}
	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {
		if (inferiorWeight) {
			this->decreaseHp();
		}
		if (this->getHp() < 1) {
			//game.remove(this);
			respawnEnemy();
		}
	}

	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		respawnEnemy();
	}
private:
	void respawnEnemy() {
		setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), this->getRect().y);
		setMoveSpeed(sys.generateRandomNumber(8, 1));
		this->setHp(defaultHp);
	}
	int defaultHp;
};

class Bullet : public MovingSprite {
public:
	Bullet(int x, int y, GameEngine& engine) : Sprite(x, y, 40, 40, true), MovingSprite(x, y, 40, 40, MovingSprite::MOVERIGHT, 20, path.fx_Bullet, 3, 0)
	{}

	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {
		//Add 100 points. Update Points label
		//Ignore collision with plane, remove bullet if it connects with inferior weighted sprites.
		if (otherSprite->getCollisionWeight() != 1) {
			cout << otherSprite->getCollisionWeight();
			game.remove(this);
		}
		//Play hit-sound
	}

	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		game.remove(this);
	}
};

class Player : public AnimatedSprite, public ControllableSprite {
public:
	Player(int x, int y, int w, int h, std::unordered_map<std::string, std::string> animationsSpriteSheets, std::string& defaultImage) :Sprite(x, y, w, h, true), AnimatedSprite(x, y, w, h, animationsSpriteSheets, defaultImage), ControllableSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3), MovingSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3)
	{}
	Player(int x, int y, int w, int h, std::unordered_map<std::string, std::vector<std::string>> animationSprites, std::string& defaultImage) :Sprite(x, y, w, h, true), AnimatedSprite(x, y, w, h, animationSprites, defaultImage), ControllableSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3), MovingSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3)
	{}

	void tick(int iterationCount) {
		AnimatedSprite::tick(game.getIterationCount());
		determineMoveDirection();
		move();
	}
	void keyDown(const SDL_Event& event)
	{
		if (isAlive) {
			implementBasicMovement(event);
			if (event.key.keysym.sym == SDLK_SPACE) {
				if (event.key.repeat == 0) { //Don't allow holding down space bar to shoot
					shoot();
				}
			}
		} if (event.key.keysym.sym == 'r') {
			isAlive = true;
			setXY(100, 100);
			setMoveLeft(false);
			setMoveUp(false);
			setMoveDown(false);
			setMoveRight(false);
		}
	}
	void keyUp(const SDL_Event& event)
	{
		if (isAlive) {
			implementBasicMovement(event);
		}

	}
	void draw() const {
		AnimatedSprite::draw();
	}
	void shoot() {
		game.add(new Bullet(getRect().x + 90, getRect().y + 53, game));
	}

	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {
		if (otherSprite->getCollisionWeight() != 3 && otherSprite->getCollisionWeight() != 1) {
			cout << otherSprite->getCollisionWeight();
			isAlive = false;
			setMoveLeft(false);
			setMoveUp(false);
			setMoveDown(true);
			setMoveRight(true);
			//Sätt Death-animation event eller liknande
		}
		//Play crash-sound
	}
private:
	bool isAlive = true;
};

int main(int argc, char** argv) {

	Background* bg_Level_1 = Background::getInstance(path.bg_Level_1);
	game.add(new Cloud(1180, 50, 256, 256, 1, path.ni_Cloud_1));
	MovingSprite* ni_Cloud_2 = new Cloud(880, 250, 450, 450, 2, path.ni_Cloud_2);
	MovingSprite* ni_Cloud_3 = new Cloud(1000, 650, 300, 300, 3, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_4 = new Cloud(570, 500, 280, 280, 2, path.ni_Cloud_2);
	MovingSprite* ni_Cloud_5 = new Cloud(350, 400, 400, 400, 1, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_6 = new Cloud(220, 800, 256, 256, 2, path.ni_Cloud_2);
	MovingSprite* ni_Cloud_7 = new Cloud(70, 100, 320, 320, 3, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_8 = new Cloud(1570, -100, 300, 300, 2, path.ni_Cloud_2);

	MovingSprite* enemy1 = new SpaceShip(1280, 350, 126, 93, MovingSprite::MOVELEFT, 2, path.e_SpaceShip, 2, 10);
	MovingSprite* enemy2 = new SpaceShip(0, 350, 126, 93, MovingSprite::MOVERIGHT, 2, path.e_SpaceShip, 2, 2);

	unordered_map<std::string, std::vector<std::string>> animations;
	animations["idle"] = vector<std::string>{ path.p_Plane_idle_1, path.p_Plane_idle_2 };
	AnimatedSprite* player = new Player(100, 350, 148, 101, animations, path.p_Plane_idle_1);

	//MovingSprite* ni_Cloud_1 = MovingSprite::getInstance(1290, 100, 0, 0, MovingSprite::MOVELEFT, 4, path.ni_Cloud_1);
	//MovingSprite* ni_Cloud_2 = MovingSprite::getInstance(0, 300, 0, 0, MovingSprite::MOVERIGHT, 4, path.ni_Cloud_1);
	//MovingSprite* ni_Cloud_3 = MovingSprite::getInstance(300, 500, 0, 0, MovingSprite::MOVEUP, 4, path.ni_Cloud_1);
	//MovingSprite* ni_Cloud_4 = MovingSprite::getInstance(700, 100, 0, 0, MovingSprite::MOVEDOWN, 4, path.ni_Cloud_1);
	game.add(bg_Level_1);
	//game.add(ni_Cloud_1);
	game.add(ni_Cloud_2);
	game.add(ni_Cloud_3);
	game.add(ni_Cloud_4);
	game.add(ni_Cloud_5);
	game.add(ni_Cloud_6);
	game.add(ni_Cloud_7);
	game.add(ni_Cloud_8);
	game.add(enemy1);
	//game.add(enemy2);
	game.add(player);

	game.run();
	//SDL_Delay(5000);
	return 0;
}