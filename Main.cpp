#include <SDL.h>
#include "GameEngine.h"
#include "Background.h"
#include "ImagePaths.h"
#include "MovingSprite.h"



using namespace planeGameEngine;
using namespace std;

//Implementation classes below
class Cloud : public MovingSprite {
public:
	Cloud(int x, int y, int w, int h, moveDirections moveDirection, int speed, std::string& imagePath) : MovingSprite(x, y, w, h, moveDirection, speed, imagePath)
	{
		
	}


	void outOfBoundsAction(SDL_Rect* rect, moveDirections moveDirection) {
		switch (moveDirection) {
		case MOVELEFT:
			setXY(sys.generateRandomNumber(sys.getXResolution() + minOutOfBoundsValue, sys.getXResolution() + maxOutOfBoundsValue), rect->y);
			break;
		}
		//case MOVERIGHT:
		//	setXY(sys.generateRandomNumber(-minOutOfBoundsValue, -maxOutOfBoundsValue), rect->y);
		//	break;
		//case MOVEUP:
		//	setXY(rect->x, sys.generateRandomNumber(sys.getYResolution() + minOutOfBoundsValue, sys.getYResolution() + maxOutOfBoundsValue));
		//	break;
		//case MOVEDOWN:
		//	setXY(rect->x, sys.generateRandomNumber(-minOutOfBoundsValue, -maxOutOfBoundsValue));
		//}
		int size = sys.generateRandomNumber(400, 256);
		setWH(size, size);
		setMoveSpeed(sys.generateRandomNumber(3, 1));
	}
private:
	const int minOutOfBoundsValue = 200;
	const int maxOutOfBoundsValue = 600;
};

int main(int argc, char** argv) {
	GameEngine game;
	ImagePaths path;
	Background* bg_Level_1 = Background::getInstance(path.bg_Level_1);
	MovingSprite* ni_Cloud_1 = new Cloud(1180, 50, 256, 256, MovingSprite::MOVELEFT, 1, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_2 = new Cloud(880, 250, 450, 450, MovingSprite::MOVELEFT, 2, path.ni_Cloud_2);
	MovingSprite* ni_Cloud_3 = new Cloud(1000, 650, 300, 300, MovingSprite::MOVELEFT, 3, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_4 = new Cloud(570, 500, 280, 280, MovingSprite::MOVELEFT, 2, path.ni_Cloud_2);
	MovingSprite* ni_Cloud_5 = new Cloud(350, 400, 400, 400, MovingSprite::MOVELEFT, 1, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_6 = new Cloud(220, 800, 256, 256, MovingSprite::MOVELEFT, 2, path.ni_Cloud_2);
	MovingSprite* ni_Cloud_7 = new Cloud(70, 100, 320, 320, MovingSprite::MOVELEFT, 3, path.ni_Cloud_1);
	MovingSprite* ni_Cloud_8 = new Cloud(1570, -100, 300, 300, MovingSprite::MOVELEFT, 2, path.ni_Cloud_2);

	//MovingSprite* ni_Cloud_1 = MovingSprite::getInstance(1290, 100, 0, 0, MovingSprite::MOVELEFT, 4, path.ni_Cloud_1);
	//MovingSprite* ni_Cloud_2 = MovingSprite::getInstance(0, 300, 0, 0, MovingSprite::MOVERIGHT, 4, path.ni_Cloud_1);
	//MovingSprite* ni_Cloud_3 = MovingSprite::getInstance(300, 500, 0, 0, MovingSprite::MOVEUP, 4, path.ni_Cloud_1);
	//MovingSprite* ni_Cloud_4 = MovingSprite::getInstance(700, 100, 0, 0, MovingSprite::MOVEDOWN, 4, path.ni_Cloud_1);

	game.add(bg_Level_1);
	game.add(ni_Cloud_1);
	game.add(ni_Cloud_2);
	game.add(ni_Cloud_3);
	game.add(ni_Cloud_4);
	game.add(ni_Cloud_5);
	game.add(ni_Cloud_6);
	game.add(ni_Cloud_7);
	game.add(ni_Cloud_8);
	game.run();
	//SDL_Delay(5000);
	return 0;
}