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
#include "Label.h"
#include "TextInputLabel.h"
#include "MemFuncShortCommand.h"

using namespace planeGameEngine;
using namespace std;
void setUp();

const int minOutOfBoundsValue = 200;
const int maxOutOfBoundsValue = 600;
int killCount;
int musicVolume = 20;
int score, bombDirectionCount;
vector<Label*> highScores;
Label* scoreLabel;
Label* highScoresLabel;
Level* level_Highscores;
ControllableSprite* playerPointer;
GameEngine game(60); //Choose Frame Rate

void volumeUp() {
	musicVolume += 2;
	Mix_VolumeMusic(musicVolume);
}
void volumeDown() {
	musicVolume -= 2;
	Mix_VolumeMusic(musicVolume);
}
void incrementScore(int nr) {
	score += nr;
	scoreLabel->setText("Score: " + to_string(score));
}
void restartGame() {
	score = 0;
	scoreLabel->setText("Score: " + to_string(score));
	playerPointer->setXY(100, 100);
	playerPointer->setAlive(true);
	playerPointer->setMoveDown(false);
	playerPointer->setMoveUp(false);
	playerPointer->setMoveLeft(false);
	playerPointer->setMoveRight(false);
	if (AnimatedSprite* p = dynamic_cast<AnimatedSprite*>(playerPointer)) {
		p->setIdleAnimation(true);
	}
	game.setLevelChange(true, 0);
	playerPointer->setAffectedByGravity(false);
	playerPointer->setGravitySpeed(0.0);
	Mix_HaltMusic();
	sys.playMusic("music", -1, 0);
	Mix_VolumeMusic(musicVolume);
}

//Implementation classes below

//Struct to demonstrate the use of memberfunction pointers.
struct PauseStruct {

	void pauseGame() {
		if (!game.isPaused()) {
			game.setPause(true);
		}
		else {
			game.setPause(false);
		}
	}
};

class Cloud : public MovingSprite {
public:
	Cloud(int x, int y, int w, int h, int speed, std::string& imagePath) : Sprite(x, y, w, h), MovingSprite(x, y, w, h, MovingSprite::MOVELEFT, speed, imagePath, 1, NULL) {}
	void tick() {
		MovingSprite::tick();
	}
	void outOfBoundsAction(SDL_Rect* rect) {
		setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), rect->y);
		int size = sys.generateRandomNumber(400, 256);
		setWH(size, size);
		setMoveSpeed(sys.generateRandomNumber(3, 1));
	}
};

class Bomb : public MovingSprite {
public:
	Bomb(int x, int y, GameEngine& engine, MovingSprite::moveDirections move) : Sprite(x, y, 0, 0, true), MovingSprite(x, y, 0, 0, move, sys.generateRandomNumber(7, 3), path.fx_Bomb, 4, 0)
	{
		setAffectedByGravity(true);
	}

	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {

		if (inferiorWeight) {
			game.removeSprite(this);
		}
	}

	void outOfBoundsAction(SDL_Rect* rect) {
		if (rect->y > sys.getYResolution()) {
			game.removeSprite(this);
		}
	}
};
class Ufo : public MovingSprite {
private:
	bool first = true;
	bool alive = true;
	int count, defaultHp;
	int bombCounter = 0;
public:
	Ufo(int x, int y, int w, int h, MovingSprite::moveDirections moveDir, int speed, std::string& imagePath, int weight, int hp) : Sprite(sys.getXResolution() + 200, sys.getYResolution() / 2, w, h, true), MovingSprite(x, y, w, h, MovingSprite::MOVELEFT, 2, path.e_Ufo, 2, 50)
	{
		defaultHp = 50;
	}
	void resetSpriteInstance() {
		setHp(defaultHp);
		first = true;
		alive = true; count = 0;
		setXY(sys.getXResolution() + 200, sys.getYResolution() / 2);
		setDirection(MovingSprite::MOVELEFT);
	}

	void tick() {
		if (alive) {

			if (first == false && bombCounter > 40) {
				if (bombDirectionCount == 0) {
					game.addSprite(new Bomb(getRect().x + 80, getRect().y - 50, game, MOVEUPLEFT));
					bombDirectionCount = 1;
				}
				else if (bombDirectionCount == 1) {
					game.addSprite(new Bomb(getRect().x + 80, getRect().y - 50, game, MOVEDOWNLEFT));
					bombDirectionCount = 2;
				}
				else if (bombDirectionCount == 2) {
					game.addSprite(new Bomb(getRect().x + 80, getRect().y - 50, game, MOVELEFT));
					bombDirectionCount = 0;
				}
				sys.playSfx(-1, "plopSound", 0);
				bombCounter = 0;
			}
			if (first && getRect().x < sys.getXResolution() - 300) {
				setDirection(MovingSprite::MOVEUP);
				first = false;
			}
			if (getRect().y < 0) {
				setDirection(MovingSprite::MOVEDOWN);
			}
			else if (getRect().y > sys.getYResolution() - getRect().h) {
				setDirection(MovingSprite::MOVEUP);
			}
			bombCounter++;
		}
		else {
			setDirection(MovingSprite::MOVEDOWNLEFT);
			if (count == 30) {
				Mix_Volume(sys.playSfx(-1, "boomSound", 0), 40);
				count = 0;
			}
			count++;
			if (getRect().y > sys.getYResolution()) {
				game.setLevelChange(true, 0);
				Mix_HaltMusic();
				sys.playMusic("music", -1, 1000);
				Mix_VolumeMusic(musicVolume);
			}
		}
		MovingSprite::tick();
	}
	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {
		if (alive && inferiorWeight && otherSprite->getCollisionWeight() != 4) {
			decreaseHp();
			incrementScore(20);
		}
		if (alive && getHp() < 1) {
			incrementScore(10000);
			alive = false;
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
		}
		if (getHp() < 1) {
			Mix_Volume(sys.playSfx(-1, "boomSound", 0), 40);
			killCount++;
			incrementScore(100);
			if (killCount > 4) {
				killCount = 0;
				game.setLevelChange(true, -1);
				Mix_HaltMusic();
				sys.playMusic("music2", -1, 1000);
				Mix_VolumeMusic(musicVolume);
			}
			respawnEnemy();
		}
	}

	void outOfBoundsAction(SDL_Rect* rect) {
		if (rect->x < 0 + getRect().w) {
			respawnEnemy();
		}
	}
private:
	void respawnEnemy() {
		setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), getDefaultPosY()); //this->getRect().y
		setMoveSpeed(sys.generateRandomNumber(9, 4));
		this->setHp(defaultHp);
	}
	int defaultHp;
};
class HighScoreLabel : public TextInputLabel {

public:
	HighScoreLabel(int x, int y, const std::string& txt, SDL_Color col) : TextInputLabel(x, y, txt, col) {}
	void perform() {

		if (!highScores.empty()) {
			highScores.push_back(Label::getInstance(highScores[highScores.size() - 1]->getRect().x, highScores[highScores.size() - 1]->getRect().y + 50, getText() + " " + to_string(score), { 255,255,255 }));
		}
		else {
			highScores.push_back(Label::getInstance(200, 150, getText() + " " + to_string(score), { 255,255,255 }));
		}

		for (unsigned i = 0; i < highScores.size(); i++) {
			level_Highscores->addSprite(highScores[i]);
		}
		game.setLevelChange(true, -1);
	}
};

class Bullet : public MovingSprite {
public:
	Bullet(int x, int y, GameEngine& engine) : Sprite(x, y, 0, 0, true), MovingSprite(x, y, 0, 0, MovingSprite::MOVERIGHT, 20, path.fx_Bullet, 3, 0)
	{
		activateBounce(true, 0.6);
	}
	void bounce(Sprite* other) {
		if (other->getCollisionWeight() == 4) {

			MovingSprite::bounce(other);
			activateBounce(false);
			setAffectedByGravity(true);
		}
	}
	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {

		//Ignore collision with plane, remove bullet if it connects with inferior weighted sprites.
		if (otherSprite->getCollisionWeight() != 1 && otherSprite->getCollisionWeight() != 4 && otherSprite->getCollisionWeight() != 3) {
			game.removeSprite(this);
		}
		//Play hit-sound
	}
	void hitBoundryAction(SDL_Rect* rect) {	}

	void outOfBoundsAction(SDL_Rect* rect) {
		game.removeSprite(this);
	}
};


class Player : public AnimatedSprite, public ControllableSprite {
public:
	Player(int x, int y, int w, int h, std::string& defaultImage) :Sprite(x, y, w, h, true), AnimatedSprite(x, y, w, h, defaultImage), ControllableSprite(x, y, w, h, MovingSprite::MOVESTOP, 5, 1, 3), MovingSprite(x, y, w, h, MovingSprite::MOVESTOP, 6, 1, 3)
	{
		setAlive(true);
	}
	void tick() {
		AnimatedSprite::tick();
		determineMoveDirection();
		move();
	}
	void keyDown(const SDL_Event& event)
	{
		if (isAlive()) {
			implementBasicMovement(event);
			if (event.key.keysym.sym == SDLK_SPACE && !game.isPaused()) {
				if (event.key.repeat == 0) { //Don't allow holding down space bar to shoot
					shoot();
				}
			}
		} if (event.key.keysym.sym == 'r') {
			setAlive(true);
			makeTextures(path.p_Plane_idle_1);
			setIdleAnimation(true);
			setAffectedByGravity(false);
			setGravitySpeed(0.0);
			setXY(100, 100);
			setMoveLeft(false);
			setMoveUp(false);
			setMoveDown(false);
			setMoveRight(false);
		}if (event.key.keysym.sym == SDLK_ESCAPE) {
			game.setLevelChange(true, 0);
			makeTextures(path.p_Plane_idle_1);
			setIdleAnimation(true);
		}
	}
	void keyUp(const SDL_Event& event)
	{
		if (isAlive()) {
			implementBasicMovement(event);
		}
	}
	void draw() {
		AnimatedSprite::draw();
	}
	void shoot() {
		game.addSprite(new Bullet(getRect().x + 90, getRect().y + 53, game));
		sys.playSfx(-1, "bulletSound", 0);
		setActiveEvent("shoot");
	}
	void collisionAction(Sprite* otherSprite, bool inferiorWeight) {
		if (isAlive() && otherSprite->getCollisionWeight() != 3 && otherSprite->getCollisionWeight() != 1) {
			Mix_Volume(sys.playSfx(-1, "boomSound2", 0), 50);
			setAlive(false);
			setAffectedByGravity(true);
			makeTextures(path.p_Plane_dead);
			setIdleAnimation(false);
		}
	}
	void outOfBoundsAction(SDL_Rect* rect) {
		//Game over, go to end-screen
		makeTextures(path.p_Plane_idle_1);
		game.setLevelChange(true, 2);
	};
};
void setUp() {
	//Setting up player
	Player* player = new Player(100, 350, 0, 0, path.p_Plane_idle_1);
	player->addAnimation("idle", { path.p_Plane_idle_1, path.p_Plane_idle_2 });
	player->addAnimation("shoot", { path.p_Plane_shooting_1, path.p_Plane_shooting_2, path.p_Plane_shooting_3, path.p_Plane_shooting_4, path.p_Plane_shooting_5 });
	playerPointer = player;

	//Setting up score-label
	scoreLabel = Label::getInstance(20, 20, "Score: 0", { 255, 255, 255 });

	// LEVEL 1 - Adding all sprites
	Level* level1 = game.addLevel();
	level1->addSprite({
		Background::getInstance(path.bg_Level_1),
		new Cloud(1180, 50, 256, 256, 1, path.ni_Cloud_1),
		new Cloud(1000, 650, 300, 300, 3, path.ni_Cloud_2),
		new Cloud(880, 250, 450, 450, 2, path.ni_Cloud_1),
		new Cloud(1570, -100, 300, 300, 2, path.ni_Cloud_2),
		new Cloud(570, 500, 280, 280, 2, path.ni_Cloud_2),
		new Cloud(350, 400, 400, 400, 1, path.ni_Cloud_1),
		new Cloud(220, 800, 256, 256, 2, path.ni_Cloud_2),
		new Cloud(70, 100, 320, 320, 3, path.ni_Cloud_2),
		new SpaceShip(1280, 150, 0, 0, MovingSprite::MOVELEFT, 10, path.e_SpaceShip, 2, 2),
		new SpaceShip(2500, 250, 0, 0, MovingSprite::MOVELEFT, 6, path.e_SpaceShip, 2, 2),
		new SpaceShip(3600, 650, 0, 0, MovingSprite::MOVELEFT, 3, path.e_SpaceShip, 2, 2),
		new SpaceShip(1570, 500, 0, 0, MovingSprite::MOVERIGHT, 7, path.e_SpaceShip, 2, 2),
		new SpaceShip(2050, 400, 0, 0, MovingSprite::MOVELEFT, 6, path.e_SpaceShip, 2, 2),
		new SpaceShip(2000, 30, 0, 0, MovingSprite::MOVERIGHT, 5, path.e_SpaceShip, 2, 2),
		scoreLabel, player
		});

	// LEVEL 2 (Boss-level) - Adding all sprites
	Level* level2 = game.addLevel();
	level2->addSprite({
		Background::getInstance(path.bg_Level_2),
		new Cloud(1180 + 1280, 50, 256, 256, 1, path.ni_Cloud_1d),
		new Cloud(880 + 1280, 250, 450, 450, 2, path.ni_Cloud_2d),
		new Cloud(1000 + 1280, 650, 300, 300, 3, path.ni_Cloud_1d),
		new Cloud(570 + 1280, 500, 280, 280, 2, path.ni_Cloud_2d),
		new Cloud(350 + 1280, 400, 400, 400, 1, path.ni_Cloud_1d),
		new Cloud(220 + 1280, 800, 256, 256, 2, path.ni_Cloud_2d),
		new Cloud(70 + 1280, 100, 320, 320, 3, path.ni_Cloud_1d),
		new Cloud(1570 + 1280, -100, 300, 300, 2, path.ni_Cloud_2d),
		new Ufo(0,0,0,0, MovingSprite::MOVELEFT,2,path.e_Ufo, 2, 100),
		scoreLabel, player
		});

	// LEVEL GAMEOVER - Adding all sprites
	Level* levelGameOver = game.addLevel();
	levelGameOver->addSprite(Background::getInstance(path.bg_Level_2));
	Label* died = Label::getInstance(sys.getXResolution() / 2 - 370, 250, "You died... please enter you name:", { 255, 255, 255 });
	HighScoreLabel* playerInputName = new HighScoreLabel(sys.getXResolution() / 2 - 120, 300, "", { 255, 255, 255 });
	levelGameOver->addSprite(died);
	levelGameOver->addSprite(playerInputName);

	// LEVEL HIGHSCORES - Adding all sprites
	level_Highscores = game.addLevel();
	level_Highscores->addSprite(Background::getInstance(path.bg_Level_2));
	highScores.push_back(Label::getInstance(sys.getXResolution() / 2 - 140, 220, "HIGHSCORES:", { 255,255,255 }));
	highScores.push_back(Label::getInstance(sys.getXResolution() / 2 - 140, 290, "Pelle 2100", { 255,255,255 }));
	highScores.push_back(Label::getInstance(sys.getXResolution() / 2 - 140, 340, "Nisse 3100", { 255,255,255 }));

	//Add sounds
	sys.addMusic("music", path.m_Level1_Music);
	sys.addMusic("music2", path.m_Level2_Music);
	sys.addSfx("bulletSound", path.sfx_BulletSound);
	sys.addSfx("boomSound", path.sfx_BoomSound_1);
	sys.addSfx("boomSound2", path.sfx_BoomSound_2);
	sys.addSfx("plopSound", path.sfx_Plop);
	sys.playMusic("music", -1, 500);
	Mix_VolumeMusic(musicVolume);
	Mix_Volume(sys.audioChannel1, 20);
	Mix_Volume(sys.audioChannel2, 20);

	//Add Short Commands (Function pointer)
	game.addFuncShortCommand('+', volumeUp); //increase music volume
	game.addFuncShortCommand('-', volumeDown); // decrease music volume
	game.addFuncShortCommand(SDLK_ESCAPE, restartGame);

	//Add Short Command (Member function pointer)
	PauseStruct ps;
	ShortCommand* mfunc = MemFuncShortCommand<PauseStruct>::getInstance('p', &ps, &PauseStruct::pauseGame);
	game.addMemFuncShortCommand(mfunc);
}
int main(int argc, char** argv) {
	setUp();
	game.run();
	return 0;
}