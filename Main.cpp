#include <SDL.h>
#include "GameEngine.h"
#include "Background.h"
#include "FilePaths.h"
#include "MovingSprite.h"
#include "AnimatedSprite.h"
#include "ControllableSprite.h"
#include <unordered_map>
#include <iostream>
#include "Level.h"

using namespace planeGameEngine;
using namespace std;

const int minOutOfBoundsValue = 200;
const int maxOutOfBoundsValue = 600;
int killCount;
int volume = 30;
GameEngine game;

void volumeUp() {
	volume += 2;
	Mix_Volume(sys.audioChannel1, volume);
}
void volumeDown() {
	volume -= 2;
	Mix_Volume(sys.audioChannel1, volume);
}

//Implementation classes below
class Cloud : public MovingSprite {
public:
	Cloud(int x, int y, int w, int h, int speed, std::string& imagePath) : Sprite(x, y, w, h), MovingSprite(x, y, w, h, MovingSprite::MOVELEFT, speed, imagePath, 1, NULL)
	{

	}
	void tick() {
		MovingSprite::tick(game.getIterationCount());
	}
	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		if (!isFlaggedForDeletion()) {

			setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), rect->y);
			int size = sys.generateRandomNumber(400, 256);
			setWH(size, size);
			setMoveSpeed(sys.generateRandomNumber(3, 1));
		}
		else {
			game.removeSprite(this);
		}
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
			decreaseHp();
			std::cout << "HIT!" << endl;
		}
		if (getHp() < 1) {
			Mix_Volume(sys.playSfx(-1, "boomSound", 0), 40);
			killCount++;
			if (killCount > 3) {
				killCount = 0;
				game.setLevelChange(true);
			}

			respawnEnemy();
			//Add 100 points. Update Points label
		}
	}

	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		respawnEnemy();
	}
private:
	void respawnEnemy() {
		if (!isFlaggedForDeletion()) {

			setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), this->getRect().y);
			setMoveSpeed(sys.generateRandomNumber(8, 3));
			this->setHp(defaultHp);
		}
		else {
			game.removeSprite(this);
		}
	}
	int defaultHp;
};

class Bullet : public MovingSprite {
public:
	Bullet(int x, int y, GameEngine& engine) : Sprite(x, y, 40, 40, true), MovingSprite(x, y, 40, 40, MovingSprite::MOVERIGHT, 20, path.fx_Bullet, 3, 0)
	{}

	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {

		//Ignore collision with plane, remove bullet if it connects with inferior weighted sprites.
		if (otherSprite->getCollisionWeight() != 1) {
			//cout << "hit " << otherSprite->getCollisionWeight() << endl; 
			game.removeSprite(this);
		}
		//Play hit-sound
	}

	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		game.removeSprite(this);
	}
};

class Player : public AnimatedSprite, public ControllableSprite {
public:
	Player(int x, int y, int w, int h, std::unordered_map<std::string, std::string> animationsSpriteSheets, std::string& defaultImage) :Sprite(x, y, w, h, true), AnimatedSprite(x, y, w, h, animationsSpriteSheets, defaultImage), ControllableSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3), MovingSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3)
	{
		setIsPlayer(true);
	}
	Player(int x, int y, int w, int h, std::unordered_map<std::string, std::vector<std::string>> animationSprites, std::string& defaultImage) :Sprite(x, y, w, h, true), AnimatedSprite(x, y, w, h, animationSprites, defaultImage), ControllableSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3), MovingSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3)
	{
		setIsPlayer(true);
	}

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
		game.addSprite(new Bullet(getRect().x + 90, getRect().y + 53, game));
		sys.playSfx(-1, "bulletSound", 0);
	}

	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {
		if (isAlive && otherSprite->getCollisionWeight() != 3 && otherSprite->getCollisionWeight() != 1) {
			Mix_Volume(sys.playSfx(-1, "boomSound2", 0), 50);
			cout << otherSprite->getCollisionWeight();
			isAlive = false;
			setMoveLeft(false);
			setMoveUp(false);
			setMoveDown(true);
			setMoveRight(true);
			//S�tt Death-animation event eller liknande
		}
		//Play crash-sound
	}
private:
	bool isAlive = true;
};

int main(int argc, char** argv) {

	Level* level1 = game.addLevel(10);

	// LEVEL 1 - Adding all sprites
	level1->addSprite({
		Background::getInstance(path.bg_Level_3),
		new Cloud(1180, 50, 256, 256, 1, path.ni_Cloud_1),
		new Cloud(1000, 650, 300, 300, 3, path.ni_Cloud_2),
		new Cloud(880, 250, 450, 450, 2, path.ni_Cloud_1),
		new Cloud(1570, -100, 300, 300, 2, path.ni_Cloud_2),
		new Cloud(570, 500, 280, 280, 2, path.ni_Cloud_2),
		new Cloud(350, 400, 400, 400, 1, path.ni_Cloud_1),
		new Cloud(220, 800, 256, 256, 2, path.ni_Cloud_2),
		new Cloud(70, 100, 320, 320, 3, path.ni_Cloud_2),
		new SpaceShip(1280, 150, 126, 93, MovingSprite::MOVELEFT, 10, path.e_SpaceShip, 2, 2),
		new SpaceShip(2500, 250, 126, 93, MovingSprite::MOVELEFT, 6, path.e_SpaceShip, 2, 2),
		new SpaceShip(3600, 650, 126, 93, MovingSprite::MOVELEFT, 3, path.e_SpaceShip, 2, 2),
		new SpaceShip(1570, 500, 126, 93, MovingSprite::MOVERIGHT, 7, path.e_SpaceShip, 2, 2),
		new SpaceShip(2050, 400, 126, 93, MovingSprite::MOVELEFT, 6, path.e_SpaceShip, 2, 2),
		new SpaceShip(2000, 30, 126, 93, MovingSprite::MOVERIGHT, 5, path.e_SpaceShip, 2, 2),
		});

	unordered_map<std::string, std::vector<std::string>> animations;
	animations["idle"] = vector<std::string>{ path.p_Plane_idle_1, path.p_Plane_idle_2 };
	Player* player = new Player(100, 350, 148, 101, animations, path.p_Plane_idle_1);
	level1->addSprite(player);

	Level* level2 = game.addLevel(1);
	level2->addSprite(Background::getInstance(path.bg_Level_2));

	level2->addSprite(new Cloud(1180 + 1280, 50, 256, 256, 1, path.ni_Cloud_1d));
	level2->addSprite(new Cloud(880 + 1280, 250, 450, 450, 2, path.ni_Cloud_2d));
	level2->addSprite(new Cloud(1000 + 1280, 650, 300, 300, 3, path.ni_Cloud_1d));
	level2->addSprite(new Cloud(570 + 1280, 500, 280, 280, 2, path.ni_Cloud_2d));
	level2->addSprite(new Cloud(350 + 1280, 400, 400, 400, 1, path.ni_Cloud_1d));
	level2->addSprite(new Cloud(220 + 1280, 800, 256, 256, 2, path.ni_Cloud_2d));
	level2->addSprite(new Cloud(70 + 1280, 100, 320, 320, 3, path.ni_Cloud_1d));
	level2->addSprite(new Cloud(1570 + 1280, -100, 300, 300, 2, path.ni_Cloud_2d));

	level2->addSprite({

		new SpaceShip(1280, 150, 126, 93, MovingSprite::MOVELEFT, 10, path.e_SpaceShip, 2, 4),
		new SpaceShip(2500, 250, 126, 93, MovingSprite::MOVELEFT, 6, path.e_SpaceShip, 2, 6),
		new SpaceShip(3600, 650, 126, 93, MovingSprite::MOVELEFT, 3, path.e_SpaceShip, 2, 3),
		new SpaceShip(1570, 500, 126, 93, MovingSprite::MOVELEFT, 7, path.e_SpaceShip, 2, 4),
		new SpaceShip(2050, 400, 126, 93, MovingSprite::MOVELEFT, 6, path.e_SpaceShip, 2, 8),
		new SpaceShip(2000, 30, 126, 93, MovingSprite::MOVELEFT, 5, path.e_SpaceShip, 2, 9),
		});

	level2->addSprite(new SpaceShip(1280, 350, 126, 93, MovingSprite::MOVELEFT, 10, path.e_SpaceShip, 2, 50));
	level2->addSprite(player);

	//Add sounds
	sys.addSfx("music", path.m_Level1_Music);
	sys.addSfx("bulletSound", path.sfx_BulletSound);
	sys.addSfx("boomSound", path.sfx_BoomSound_1);
	sys.addSfx("boomSound2", path.sfx_BoomSound_2);
	sys.audioChannel1 = sys.playSfx(0, "music", -1);
	Mix_Volume(sys.audioChannel1, 20);
	Mix_Volume(sys.audioChannel2, 20);

	//Short Commands
	game.addShortCommand('+', volumeUp);
	game.addShortCommand('-', volumeDown);
	game.run();

	return 0;
}


