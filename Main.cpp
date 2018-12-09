#include <SDL.h>
#include "GameEngine.h"
#include "Background.h"
#include "ImagePaths.h"

using namespace planeGameEngine;
using namespace std;

int main(int argc, char** argv) {
	GameEngine game;
	ImagePaths path;
	Background* bg_Level_1 = Background::getInstance(path.bg_Level_1);
	game.add(bg_Level_1);
	game.run();
	//SDL_Delay(5000);
	return 0;
}