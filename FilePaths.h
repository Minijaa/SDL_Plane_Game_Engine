#ifndef IMAGEPATHS_H
#define IMAGEPATHS_H
#include <string>

namespace planeGameEngine {

	//Path variables to image, sound and font files. Data members are made public 
	//in order for quick and easy access and editing.
	class FilePaths {
	public:
		//IMAGES:
			//Background Sprites [bg]
		std::string bg_Level_1 = "Images/background.png";
		std::string bg_Level_2 = "Images/background_night.png";

		//Non-interactable Sprites [ni] 
		std::string ni_Cloud_1 = "Images/Cloud1.png";
		std::string ni_Cloud_2 = "Images/Cloud2.png";
		std::string ni_Cloud_1d = "Images/Cloud1_dark.png";
		std::string ni_Cloud_2d = "Images/Cloud2_dark.png";

		//Effects [fx]
		std::string fx_Bullet = "Images/Bullet.png";
		std::string fx_Bomb = "Images/bomb.png";

		//Player Sprites [p]
		std::string p_Plane_idle_1 = "Images/Fly1.png";
		std::string p_Plane_idle_2 = "Images/Fly2.png";
		std::string p_Plane_shooting_1 = "Images/Shoot1.png";
		std::string p_Plane_shooting_2 = "Images/Shoot2.png";
		std::string p_Plane_shooting_3 = "Images/Shoot3.png";
		std::string p_Plane_shooting_4 = "Images/Shoot4.png";
		std::string p_Plane_shooting_5 = "Images/Shoot5.png";
		std::string p_Plane_dead = "Images/Dead.png";

		//Enemy Sprites [e]
		std::string e_SpaceShip = "Images/Enemy1.png";
		std::string e_Ufo = "Images/Ufo.png";

		//SOUNDS:
			//Sound Effect [sfx]
		std::string sfx_BulletSound = "Sfx/shot.wav";
		std::string sfx_BoomSound_1 = "Sfx/boom.wav";
		std::string sfx_BoomSound_2 = "Sfx/boom2.wav";
		std::string sfx_Plop = "Sfx/plop.wav";

		//Music [m]
		std::string m_Level1_Music = "Sfx/L1Music.mp3";
		std::string m_Level2_Music = "Sfx/L2Music.mp3";

		//FONTS [f]:
		std::string f_BauhausFont = "Fonts/BAUHS93.TTF";
		std::string f_GilsansFont = "Fonts/GILSANUB.TTF";
	};
	extern FilePaths path;
}
#endif // !IMAGEPATHS_H
